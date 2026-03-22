#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

# fmt: off

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "R89JEL",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Extra flags for clangd parser
config.extra_clang_flags = [
    "-Iinclude/MSL/internal", # Allow clangd to see internal MSL headers
    "-Wno-invalid-offsetof",  # Silence non-POD offsetof 
    "-fshort-wchar",          # Force wide characters as 16-bit 
]

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20250812"
config.dtk_tag = "v1.7.5"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-proc gekko",
    "-fp hardware",
    "-enum int",
    "-cpp_exceptions off",
    "-nosyspath",
    "-i include",
    "-i include/context_sdk",
    "-i include/context_std",
    "-i include/Runtime.PPCEABI.H",
    "-enc SJIS",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"'
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-O4,p",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# SDK library flags (todo)
cflags_sdk = [
    *cflags_base,
    "-opt off",
    "-inline off",
    "-g",
]

cflags_rfl = [
    *cflags_base,
    "-opt off",
    "-cpp_exceptions off",
    "-inline off",
    "-g",
]

config.linker_version = "GC/3.0a5.2"


# Helper function for SDK libraries
def SDKLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_sdk,
        "progress_category": "sdk",
        "objects": objects,
    }

def RFLLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_rfl,
        "progress_category": "sdk",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = False
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(Matching,    "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(Matching,    "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    
    SDKLib("vf", [
            Object(Matching,    "vf/pf_clib.c"),
            Object(Matching,    "vf/pf_code.c"),
            Object(Equivalent,  "vf/pf_service.c"),
            Object(Matching,    "vf/pf_str.c"),
            Object(Matching,    "vf/pf_w_clib.c"),
            Object(Matching,    "vf/pf_driver.c"),
            Object(Equivalent,  "vf/pdm_bpb.c"),
            Object(Equivalent,  "vf/pdm_disk.c"),
            Object(Matching,    "vf/pdm_partition.c"),
            Object(Equivalent,  "vf/pdm_mbr.c"),
            Object(Matching,    "vf/pdm_dskmng.c"),
            Object(Equivalent,  "vf/pf_cache.c"),
            Object(Matching,    "vf/pf_cluster.c"),
            Object(Equivalent,  "vf/pf_dir.c"),
            Object(NonMatching, "vf/pf_entry.c"),
            Object(NonMatching, "vf/pf_entry_iterator.c"),
            Object(NonMatching, "vf/pf_fat.c"),
            Object(NonMatching, "vf/pf_fat12.c"),
            Object(NonMatching, "vf/pf_fat16.c"),
            Object(NonMatching, "vf/pf_fat32.c"),
            Object(NonMatching, "vf/pf_fatfs.c"),
            Object(NonMatching, "vf/pf_file.c"),
            Object(NonMatching, "vf/pf_path.c"),
            Object(NonMatching, "vf/pf_sector.c"),
            Object(NonMatching, "vf/pf_volume.c"),
            Object(Matching,    "vf/pf_cp932.c"),
            Object(NonMatching, "vf/pf_api_util.c"),
            Object(NonMatching, "vf/pf_attach.c"),
            Object(NonMatching, "vf/pf_detach.c"),
            Object(NonMatching, "vf/pf_errnum.c"),
            Object(NonMatching, "vf/pf_fclose.c"),
            Object(NonMatching, "vf/pf_finfo.c"),
            Object(NonMatching, "vf/pf_fopen.c"),
            Object(NonMatching, "vf/pf_format.c"),
            Object(NonMatching, "vf/pf_fread.c"),
            Object(NonMatching, "vf/pf_fseek.c"),
            Object(NonMatching, "vf/pf_fwrite.c"),
            Object(NonMatching, "vf/pf_getdev.c"),
            Object(NonMatching, "vf/pf_init_prfile2.c"),
            Object(NonMatching, "vf/pf_mkdir.c"),
            Object(NonMatching, "vf/pf_remove.c"),
            Object(NonMatching, "vf/pf_unmount.c"),
            Object(NonMatching, "vf/pf_filelock.c"),
            Object(NonMatching, "vf/pf_system.c"),
            Object(NonMatching, "vf/d_vf.c"),
            Object(NonMatching, "vf/d_vf_sys.c"),
            Object(NonMatching, "vf/d_hash.c"),
            Object(NonMatching, "vf/d_time.c"),
            Object(NonMatching, "vf/d_common.c"),
            Object(NonMatching, "vf/nand_drv.c"),
            Object(Matching,    "vf/sd_drv.c"),
        ]
    ),
    
    SDKLib("atok", [
            Object(NonMatching, "atok/build/atok.c"),
            Object(NonMatching, "atok/Src/atok_eng.c"),
            Object(NonMatching, "atok/MonPE/ApLib.c"),
            Object(NonMatching, "atok/MonPE/ApAICore.c"),
            Object(NonMatching, "atok/MonPE/ApAIDic.c"),
            Object(NonMatching, "atok/MonPE/ApCore.c"),
            Object(NonMatching, "atok/MonPE/ApDic.c"),
        ]
    ),
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
