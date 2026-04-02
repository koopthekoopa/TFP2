#include <private/vf/pf_cache.h>
#include <private/vf/pf_clib.h>
#include <private/vf/pf_driver.h>
#include <private/vf/pf_volume.h>

#include <private/vf/d_common.h>

static pf_s32 VFiPFCACHE_InitPageList(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* pages, PF_CACHE_BUFFER* buffers, pf_u16 num,
                                      pf_u32 size, pf_bool is_fat) {
    pf_u32 i;
    pf_u32 bps_per_buf;

    *pp_head = pages;
    bps_per_buf = (pf_u16)(p_vol->bpb.bytes_per_sector >> 9);
    bps_per_buf *= size;
    if (((is_fat == PF_TRUE) && ((pf_u32)(num / bps_per_buf) < 1U)) || ((is_fat == PF_FALSE) && ((pf_u32)(num / bps_per_buf) < 2U))) {
        return 0x1E;
    }
    if ((pf_u32)(num / bps_per_buf) == 1) {
        pages->p_prev = pages;
        pages->p_next = pages;
        pages->buffer = *buffers;
        pages->p_buf = *buffers;
        pages->p_mod_sbuf = PF_NULL;
        pages->p_mod_ebuf = PF_NULL;
        pages->size = size;
        pages->sector = -1U;
        pages->option = 0;
        pages->signature = PF_NULL;
        pages->stat &= ~3;
        if (is_fat) {
            pages->stat |= 4;
        } else {
            pages->stat &= ~4;
        }
        return 0;
    }
    pages->p_prev = &pages[(num - (num % bps_per_buf)) - bps_per_buf];
    pages->p_next = &pages[bps_per_buf];
    pages->buffer = *buffers;
    pages->p_buf = *buffers;
    pages->p_mod_sbuf = PF_NULL;
    pages->p_mod_ebuf = PF_NULL;
    pages->size = size;
    pages->sector = -1U;
    pages->option = 0;
    pages->signature = PF_NULL;
    pages->stat &= ~3;
    if (is_fat) {
        pages->stat |= 4;
    } else {
        pages->stat &= ~4;
    }

    for (i = bps_per_buf; i < (pf_u32)((num - (num % bps_per_buf)) - bps_per_buf); i += bps_per_buf) {
        pages[i].p_prev = &pages[i - bps_per_buf];
        pages[i].p_next = &pages[i + bps_per_buf];
        pages[i].buffer = buffers[i];
        pages[i].p_buf = buffers[i];
        pages[i].p_mod_sbuf = PF_NULL;
        pages[i].p_mod_ebuf = PF_NULL;
        pages[i].size = size;
        pages[i].sector = -1U;
        pages[i].option = 0;
        pages[i].signature = PF_NULL;
        pages[i].stat &= ~3;
        if (is_fat) {
            pages[i].stat |= 4;
        } else {
            pages[i].stat &= ~4;
        }
    }
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_prev = &pages[((num - (num % bps_per_buf)) - bps_per_buf) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_next = pages;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].buffer = buffers[(num - (num % bps_per_buf)) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_buf = buffers[(num - (num % bps_per_buf)) - bps_per_buf];
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_mod_sbuf = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].p_mod_ebuf = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].size = size;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].sector = -1U;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].option = 0;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].signature = PF_NULL;
    pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= ~3;
    if (is_fat) {
        pages[(num - (num % bps_per_buf)) - bps_per_buf].stat |= 4;
    } else {
        pages[(num - (num % bps_per_buf)) - bps_per_buf].stat &= ~4;
    }
    return 0;
}

static PF_CACHE_PAGE* VFiPFCACHE_SearchForPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_head, pf_u32 sector) {
    PF_CACHE_PAGE* p_page;

    if (sector == -1) {
        return PF_NULL;
    }

    p_page = p_head;
    if ((p_page->stat & 1) == 0) {
        return PF_NULL;
    }

    if ((p_page->sector <= sector) && (((p_page->sector + p_page->size) - 1) >= sector)) {
        p_page->p_buf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
        return p_page;
    }

    for (p_page = p_page->p_next; p_page != p_head; p_page = p_page->p_next) {
        if ((p_page->stat & 1) == 0) {
            return PF_NULL;
        }
        if ((p_page->sector <= sector) && (((p_page->sector + p_page->size) - 1) >= sector)) {
            p_page->p_buf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
            return p_page;
        }
    }
    return PF_NULL;
}

// DEBUG NON MATCHING
static PF_CACHE_PAGE* VFiPFCACHE_SearchForUsedPage(PF_VOLUME* p_vol /* r3 */, PF_CACHE_PAGE** pp_head /* r4 */, PF_CACHE_PAGE* p_page /* r5 */) {
    PF_CACHE_PAGE* lp_page;  // r31

    if (p_page == PF_NULL) {
        lp_page = *pp_head;
    } else {
        lp_page = p_page->p_next;
        if (lp_page == *pp_head) {
            return PF_NULL;
        }
    }

    while ((lp_page->stat & 1) != 0) {
        if (lp_page->sector != -1) {
            lp_page->p_buf = lp_page->buffer;
            return lp_page;
        }
        lp_page = lp_page->p_next;
    }

    return PF_NULL;
}

static pf_u32 VFiPFCACHE_SearchForFreePage(PF_CACHE_PAGE* p_head, PF_CACHE_PAGE** pp_page) {
    PF_CACHE_PAGE* p_page;

    p_page = p_head->p_prev;

    goto block;

    while (PF_TRUE) {
        if ((p_page->stat & 1) == 0) {
            *pp_page = p_page;
            return 1;
        }
        if (p_page->sector != -1) {
            *pp_page = p_page;
            return 0;
        }
        p_page = p_page->p_prev;

    block:
        if (p_page == p_head) {
            if ((p_page->stat & 1) == 0) {
                *pp_page = p_page;
                return 1;
            }
            if (p_page->sector != -1) {
                *pp_page = p_page;
                return 0;
            }
            *pp_page = PF_NULL;
            return 0;
        }
    }
}

static void VFiPFCACHE_MovePageToHead(PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* p_page) {
    if (p_page != (PF_CACHE_PAGE*)*pp_head) {
        if (p_page == (PF_CACHE_PAGE*)(*pp_head)->p_prev) {
            *pp_head = p_page;
            return;
        }
        p_page->p_prev->p_next = p_page->p_next;
        p_page->p_next->p_prev = p_page->p_prev;
        p_page->p_next = *pp_head;
        p_page->p_prev = (*pp_head)->p_prev;
        p_page->p_next->p_prev = p_page;
        p_page->p_prev->p_next = p_page;
        *pp_head = p_page;
    }
}

static void VFiPFCACHE_MovePageToTail(PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* p_page) {
    if (p_page == (PF_CACHE_PAGE*)*pp_head) {
        *pp_head = p_page->p_next;
        return;
    }
    if (p_page != (PF_CACHE_PAGE*)(*pp_head)->p_prev) {
        p_page->p_prev->p_next = p_page->p_next;
        p_page->p_next->p_prev = p_page->p_prev;
        p_page->p_next = *pp_head;
        p_page->p_prev = (*pp_head)->p_prev;
        p_page->p_next->p_prev = p_page;
        p_page->p_prev->p_next = p_page;
    }
}

static pf_s32 VFiPFCACHE_FlushPageIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    pf_s32 err;
    pf_u32 num_success;
    pf_u32 size;
    pf_u32 sectocr;
    pf_u8* p_buf;

    if ((p_page != PF_NULL) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
        p_buf = p_page->p_mod_sbuf;
        sectocr = p_page->sector + ((pf_u32)(p_page->p_mod_sbuf - p_page->buffer) >> p_vol->bpb.log2_bytes_per_sector);
        size =
            (((pf_u32)p_page->p_mod_ebuf >> p_vol->bpb.log2_bytes_per_sector) - ((pf_u32)p_page->p_mod_sbuf >> p_vol->bpb.log2_bytes_per_sector)) + 1;
        err = VFiPFDRV_lwrite(p_vol, p_buf, sectocr, size, &num_success);
        if (err != 0) {
            return err;
        }
        if (num_success != size) {
            return 0x11;
        }
        if ((p_page->stat & 4) != 0) {
            err = VFiPFFAT_UpdateAlternateFATEntry(p_vol, p_buf, sectocr, size);
            if (err != 0) {
                return err;
            }
        }
        p_page->p_mod_sbuf = PF_NULL;
        p_page->p_mod_ebuf = PF_NULL;
        p_page->stat &= 0xFFFFFFFD;
    }

    return 0;
}

static pf_s32 VFiPFCACHE_ClearModified(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_head) {
    PF_CACHE_PAGE* p_page;

    p_page = p_head;

    do {
        if ((p_page->stat & 1) == 0) {
            break;
        }
        p_page->stat &= ~2;
        p_page = p_page->p_next;
    } while (p_page != p_head);
    return 0;
}

static pf_s32 VFiPFCACHE_DoAllocatePage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_u32* p_is_hit) {
    pf_s32 err;
    pf_u32 offset;
    pf_u32 data_start_sector;
    pf_s32 do_flush;

    do_flush = 0;
    *pp_page = VFiPFCACHE_SearchForPage(p_vol, *pp_head, sector);
    if (*pp_page != 0) {
        *p_is_hit = 1;
    } else {
        *p_is_hit = 0;
        if (VFiPFCACHE_SearchForFreePage(*pp_head, pp_page) == 0) {
            PF_CACHE_PAGE* p_page;
            if (*pp_page == 0) {
                *pp_page = PF_NULL;
                return 0x1E;
            }
            p_page = *pp_page;
            if ((p_page != 0) && ((p_page->stat & 2) != 0) && ((p_page->sector) != -1)) {
                do_flush = 1;
            }
            err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &**pp_page);
            if (err != 0) {
                *pp_page = PF_NULL;
                return err;
            }
            (*pp_page)->p_mod_sbuf = PF_NULL;
            (*pp_page)->p_mod_ebuf = PF_NULL;
            if ((do_flush != 0) && (dCommon_FlushFromVol(p_vol, 1) != 0)) {
                return 0x11;
            }
        }

        if (sector != -1) {
            if (((*pp_page)->stat & 4) != 0) {
                offset = sector - p_vol->bpb.num_reserved_sectors;
                offset %= p_vol->bpb.sectors_per_FAT;
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            } else {
                if (p_vol->bpb.fat_type == FAT_32) {
                    if ((sector >= p_vol->bpb.first_data_sector) && (sector < p_vol->bpb.total_sectors)) {
                        data_start_sector = p_vol->bpb.first_data_sector;
                    } else if (sector == p_vol->bpb.fs_info_sector) {
                        data_start_sector = p_vol->bpb.fs_info_sector;
                        (*pp_page)->size = 1;
                    }
                } else {
                    data_start_sector = p_vol->bpb.first_root_dir_sector;
                }
                offset = sector - data_start_sector;
                (*pp_page)->sector = sector - (sector % (*pp_page)->size);
                (*pp_page)->p_buf = &(*pp_page)->buffer[(sector % (*pp_page)->size) << p_vol->bpb.log2_bytes_per_sector];
            }
        } else {
            (*pp_page)->sector = sector;
            (*pp_page)->p_buf = (*pp_page)->buffer;
        }
        (*pp_page)->stat |= 1;
    }
    VFiPFCACHE_MovePageToHead(pp_head, *pp_page);
    return 0;
}

static void VFiPFCACHE_DoFreeCachePage(PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* p_page) {
    p_page->stat &= ~3;
    p_page->p_mod_sbuf = PF_NULL;
    p_page->p_mod_ebuf = PF_NULL;
    p_page->sector = -1U;
    p_page->signature = PF_NULL;

    VFiPFCACHE_MovePageToTail(pp_head, p_page);
}

static pf_s32 VFiPFCACHE_DoReadPage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_u32 num_success;
    pf_u32 is_hit;
    pf_s32 err;

    err = VFiPFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    if (is_hit == 0) {
        err = VFiPFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err != 0) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return err;
        }
        if ((num_success != (*pp_page)->size) && (p_vol->bpb.total_sectors != ((*pp_page)->sector + num_success))) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return 0x11;
        }
        (*pp_page)->stat = (*pp_page)->stat & 0xFFFFFFFD;
        (*pp_page)->p_mod_sbuf = PF_NULL;
        (*pp_page)->p_mod_ebuf = PF_NULL;
        if (set_sig != 0) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = PF_NULL;
        }
    }

    return 0;
}

static pf_s32 VFiPFCACHE_DoReadPageAndFlushIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u32 sector, PF_CACHE_PAGE** pp_page,
                                                    pf_bool set_sig) {
    pf_u32 num_success;
    pf_u32 is_hit;
    pf_s32 err;
    pf_s32 do_flush;

    do_flush = 1;
    err = VFiPFCACHE_DoAllocatePage(p_vol, pp_head, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    if (is_hit == 0) {
        err = VFiPFDRV_lread(p_vol, (*pp_page)->buffer, (*pp_page)->sector, (*pp_page)->size, &num_success);
        if (err != 0) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return err;
        }
        if (((pf_u32)num_success != (pf_u32)(*pp_page)->size) && ((pf_u32)p_vol->bpb.total_sectors != (pf_u32)((*pp_page)->sector + num_success))) {
            VFiPFCACHE_DoFreeCachePage(pp_head, *pp_page);
            return 0x11;
        }
        (*pp_page)->stat = (*pp_page)->stat & 0xFFFFFFFD;
        (*pp_page)->p_mod_sbuf = PF_NULL;
        (*pp_page)->p_mod_ebuf = PF_NULL;
        if (set_sig != 0) {
            (*pp_page)->signature = p_vol->cache.signature;
        } else {
            (*pp_page)->signature = PF_NULL;
        }
    } else if ((set_sig != 0) && (((*pp_page)->stat & 2) != 0) && ((p_vol->cache.mode & 2) != 0) &&
               ((void*)(*pp_page)->signature != (void*)p_vol->cache.signature)) {
        PF_CACHE_PAGE* p_page;
        p_page = *pp_page;
        if ((p_page != 0) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
            do_flush = 1;
        }
        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &**pp_page);
        if (err != 0) {
            *pp_page = PF_NULL;
            return err;
        }
        if ((do_flush != 0) && (dCommon_FlushFromVol(p_vol, 1) != 0)) {
            return 0x11;
        }
    }

    return 0;
}

static pf_s32 VFiPFCACHE_DoReadNumSector(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector,
                                         pf_u32* p_num_success) {
    PF_CACHE_PAGE* p_page;
    pf_s32 err;
    pf_u32 num_rest_sector;
    pf_u32 num_success_sector;

    *p_num_success = 0;
    err = VFiPFDRV_lread(p_vol, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    p_page = PF_NULL;
    num_rest_sector = *p_num_success;
    num_success_sector = *p_num_success;

    do {
        p_page = VFiPFCACHE_SearchForUsedPage(p_vol, pp_head, p_page);
        if ((p_page != PF_NULL) && (p_page->sector != -1)) {
            if ((p_page->sector <= sector) && ((p_page->sector + p_page->size) >= (sector + num_success_sector))) {
                VFipf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector],
                             num_success_sector << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= num_success_sector;
            } else if ((p_page->sector >= sector) && ((p_page->sector + p_page->size) <= (sector + num_success_sector))) {
                VFipf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer,
                             p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
            } else if ((p_page->sector > sector) && (p_page->sector < (sector + num_success_sector)) &&
                       ((p_page->sector + p_page->size) >= (sector + num_success_sector))) {
                VFipf_memcpy(&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector], p_page->buffer,
                             (p_page->size - ((p_page->sector + p_page->size) - (sector + num_success_sector))) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - ((p_page->sector + p_page->size) - (sector + num_success_sector));
            } else if ((p_page->sector < sector) && ((p_page->sector + p_page->size) > sector) &&
                       ((p_page->sector + p_page->size) <= (sector + num_success_sector))) {
                VFipf_memcpy(p_buf, &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector],
                             (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
            }
        }
    } while ((p_page != PF_NULL) && (num_rest_sector != 0));

    if ((*p_num_success != num_sector) && (p_vol->bpb.total_sectors != (sector + *p_num_success))) {
        return 0x11;
    }
    return 0;
}

static pf_s32 VFiPFCACHE_DoWritePage(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, PF_CACHE_PAGE* p_page, pf_bool set_sig) {
    pf_s32 err;
    pf_s32 do_flush;

    do_flush = 0;
    VFiPFCACHE_MovePageToHead(pp_head, p_page);
    VFiPFCACHE_UpdateModifiedSector(p_page);
    if (set_sig != 0) {
        p_page->signature = p_vol->cache.signature;
    } else {
        p_page->signature = PF_NULL;
    }
    if (((p_vol->cache.mode & 1) != 0) || (((p_vol->cache.mode & 4) != 0) && ((p_page->stat & 4) != 0))) {
        if ((p_page != 0) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
            do_flush = 1;
        }
        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &*p_page);
        if (err != 0) {
            return err;
        }
        if ((do_flush != 0) && (dCommon_FlushFromVol(p_vol, 1) != 0)) {
            return 0x11;
        }
    }

    return 0;
}

static pf_s32 VFiPFCACHE_DoWriteSector(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, const pf_u8* p_buf, pf_u32 sector) {
    PF_CACHE_PAGE* p_page;
    pf_u32 num_success;
    pf_s32 err;
    pf_s32 do_flush;

    do_flush = 0;
    p_page = VFiPFCACHE_SearchForPage(p_vol, *pp_head, sector);
    if (p_page != 0) {
        VFipf_memcpy(p_page->p_buf, (pf_u8*)p_buf, p_vol->bpb.bytes_per_sector);
        VFiPFCACHE_UpdateModifiedSector(p_page);
        if ((p_page != 0) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
            do_flush = 1;
        }
        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &*p_page);
        if (err != 0) {
            return err;
        }
        if ((do_flush != 0) && (dCommon_FlushFromVol(p_vol, 1) != 0)) {
            return 0x11;
        }
    } else {
        err = VFiPFDRV_lwrite(p_vol, p_buf, sector, 1, &num_success);
        if (err != 0) {
            return err;
        }
        if (num_success != 1) {
            return 0x11;
        }
        if (dCommon_FlushFromVol(p_vol, 1) != 0) {
            return 0x11;
        }
    }

    return 0;
}

static pf_s32 VFiPFCACHE_DoWriteNumSectorAndFreeIfNeeded(PF_VOLUME* p_vol, PF_CACHE_PAGE** pp_head, const pf_u8* p_buf, pf_u32 sector,
                                                         pf_u32 num_sector, pf_u32* p_num_success) {
    PF_CACHE_PAGE* p_page;
    pf_s32 err;
    pf_u32 num_rest_sector;
    pf_u8* p_sbuf;
    pf_u8* p_ebuf;

    p_page = PF_NULL;
    num_rest_sector = num_sector;
    *p_num_success = 0;
loop_1:
    do {
        p_page = VFiPFCACHE_SearchForUsedPage(p_vol, pp_head, p_page);
        if ((p_page != PF_NULL) && (p_page->sector != -1)) {
            if ((p_page->sector <= sector) && ((p_page->sector + p_page->size) >= (sector + num_sector))) {
                VFipf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (pf_u8*)p_buf,
                             num_sector << p_vol->bpb.log2_bytes_per_sector);
                *p_num_success += num_rest_sector;
                num_rest_sector = 0;
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector];
                p_ebuf = &(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector])[(num_sector - 1)
                                                                                                           << p_vol->bpb.log2_bytes_per_sector];
                if ((pf_u8*)p_page->p_mod_sbuf == PF_NULL) {
                    p_page->p_mod_sbuf = p_sbuf;
                    p_page->p_mod_ebuf = p_ebuf;
                } else if (p_sbuf < p_page->p_mod_sbuf) {
                    p_page->p_mod_sbuf = p_sbuf;
                } else if ((pf_u8*)p_page->p_mod_ebuf < p_ebuf) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if ((p_page->sector >= sector) && ((p_page->sector + p_page->size) <= (sector + num_sector))) {
                VFipf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                             p_page->size << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size;
                *p_num_success += p_page->size;
                p_page->stat |= 2;
                p_page->p_mod_sbuf = p_page->buffer;
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            } else if ((p_page->sector > sector) && (p_page->sector < (sector + num_sector)) &&
                       ((p_page->sector + p_page->size) >= (sector + num_sector))) {
                VFipf_memcpy(p_page->buffer, (pf_u8*)&p_buf[(p_page->sector - sector) << p_vol->bpb.log2_bytes_per_sector],
                             (p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector))) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector));
                *p_num_success += p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector));
                p_page->stat |= 2;
                p_ebuf = &p_page->buffer[((p_page->size - ((p_page->sector + p_page->size) - (sector + num_sector))) - 1)
                                         << p_vol->bpb.log2_bytes_per_sector];
                p_page->p_mod_sbuf = p_page->buffer;
                if ((p_page->p_mod_ebuf == 0) || ((pf_u8*)p_page->p_mod_ebuf < p_ebuf)) {
                    p_page->p_mod_ebuf = p_ebuf;
                }
            } else if ((p_page->sector < sector) && ((p_page->sector + p_page->size) > sector) &&
                       ((p_page->sector + p_page->size) <= (sector + num_sector))) {
                VFipf_memcpy(&p_page->buffer[(sector - p_page->sector) << p_vol->bpb.log2_bytes_per_sector], (pf_u8*)p_buf,
                             (p_page->size - (sector - p_page->sector)) << p_vol->bpb.log2_bytes_per_sector);
                num_rest_sector -= p_page->size - (sector - p_page->sector);
                *p_num_success += p_page->size - (sector - p_page->sector);
                p_page->stat |= 2;
                p_sbuf = &p_page->buffer[((p_page->size - (sector - p_page->sector)) - 1) << p_vol->bpb.log2_bytes_per_sector];
                if (((pf_u8*)p_page->p_mod_sbuf == PF_NULL) || (p_sbuf < p_page->p_mod_sbuf)) {
                    p_page->p_mod_sbuf = p_sbuf;
                }
                p_page->p_mod_ebuf = &p_page->buffer[(p_page->size - 1) << p_vol->bpb.log2_bytes_per_sector];
            }
        }
    } while ((p_page != PF_NULL) && (num_rest_sector != 0));
    if ((num_rest_sector != 0) || ((p_vol->cache.mode & 1) != 0)) {
        err = VFiPFDRV_lwrite(p_vol, p_buf, sector, num_sector, p_num_success);
        if (err != 0) {
            return err;
        }
        if (dCommon_FlushFromVol(p_vol, 1) != 0) {
            return 0x11;
        }
    }

    if (((p_vol->cache.mode & 1) != 0) && (num_sector != num_rest_sector)) {
        VFiPFCACHE_ClearModified(p_vol, p_vol->cache.p_current_data);
    }
    return 0;
}

static pf_s32 VFiPFCACHE_DoFlushCache(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_head) {
    PF_CACHE_PAGE* p_page;
    pf_s32 err;
    pf_s32 first_err;
    pf_s32 check_do_flush;
    pf_s32 do_flush;

    check_do_flush = 0;
    do_flush = 0;
    first_err = 0;
    p_page = p_head;
    if ((p_page->stat & 1) == 0) {
        return 0;
    }

    do {
        if ((p_page->stat & 1) == 0) {
            break;
        }
        check_do_flush = 0;
        if ((p_page != PF_NULL) && ((p_page->stat & 2) != 0) && p_page->sector != -1) {
            check_do_flush = 1;
        }
        err = VFiPFCACHE_FlushPageIfNeeded(p_vol, p_page);
        if ((check_do_flush != 0) && (err == 0)) {
            do_flush = 1;
        }
        if ((err != 0) && (first_err == 0)) {
            first_err = err;
        }
        p_page = &*p_page->p_next;
    } while (p_page != p_head);

    if (do_flush != 0) {
        pf_s32 set_device_err = first_err != 0 ? 0 : 1;
        if ((dCommon_FlushFromVol(p_vol, set_device_err) != 0) && (set_device_err == 1)) {
            return 0x11;
        }
    }

    return first_err;
}

void VFiPFCACHE_SetCache(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_cache_page, PF_CACHE_BUFFER* p_cache_buf, pf_u16 num_fat_pages, pf_u16 num_data_pages) {
    p_vol->cache.pages = p_cache_page;
    p_vol->cache.buffers = p_cache_buf;
    p_vol->cache.num_fat_pages = num_fat_pages;
    p_vol->cache.num_data_pages = num_data_pages;
}

void VFiPFCACHE_SetFATBufferSize(PF_VOLUME* p_vol, pf_u32 size) {
    if (size != 0) {
        p_vol->cache.fat_buff_size = size;
    }
}

void VFiPFCACHE_SetDataBufferSize(PF_VOLUME* p_vol, pf_u32 size) {
    if (size != 0) {
        p_vol->cache.data_buff_size = size;
    }
}

pf_s32 VFiPFCACHE_InitCaches(PF_VOLUME* p_vol) {
    pf_s32 err;

    p_vol->cache.mode &= ~1;
    p_vol->cache.mode |= 2;
    p_vol->cache.mode &= ~4;
    VFipf_memset(p_vol->cache.buffers, 0, (p_vol->cache.num_fat_pages + p_vol->cache.num_data_pages) << 9);
    err = VFiPFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_fat, p_vol->cache.pages, p_vol->cache.buffers, p_vol->cache.num_fat_pages,
                                  p_vol->cache.fat_buff_size, PF_TRUE);
    if (err != 0) {
        return err;
    }
    err = VFiPFCACHE_InitPageList(p_vol, &p_vol->cache.p_current_data, &p_vol->cache.pages[p_vol->cache.num_fat_pages],
                                  (PF_CACHE_BUFFER*)p_vol->cache.buffers[p_vol->cache.num_fat_pages], p_vol->cache.num_data_pages,
                                  p_vol->cache.data_buff_size, PF_FALSE);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_UpdateModifiedSector(PF_CACHE_PAGE* p_page) {
    if (p_page->p_mod_sbuf == PF_NULL) {
        p_page->stat |= 2;
        p_page->p_mod_sbuf = p_page->p_buf;
        p_page->p_mod_ebuf = &*p_page->p_buf;
    } else if (p_page->p_buf < p_page->p_mod_sbuf) {
        p_page->p_mod_sbuf = p_page->p_buf;
    } else if (p_page->p_buf > p_page->p_mod_ebuf) {
        p_page->p_mod_ebuf = &*p_page->p_buf;
    }
    return 0;
}

pf_s32 VFiPFCACHE_AllocateFATPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page) {
    pf_s32 err;
    pf_u32 is_hit;

    if (p_vol->cache.p_current_fat == 0) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    }
    err = VFiPFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_AllocateDataPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page) {
    pf_s32 err;
    pf_u32 is_hit;

    if (p_vol->cache.p_current_data == 0) {
        p_vol->cache.pages->buffer = *p_vol->cache.buffers;
        p_vol->cache.pages->p_buf = *p_vol->cache.buffers;
        *pp_page = p_vol->cache.pages;
        return 0;
    }
    err = VFiPFCACHE_DoAllocatePage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, &is_hit);
    if (err != 0) {
        return err;
    }
    return 0;
}

void VFiPFCACHE_FreeFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_fat != 0) {
        p_page->p_mod_sbuf = PF_NULL;
        p_page->p_mod_ebuf = PF_NULL;
        VFiPFCACHE_DoFreeCachePage(&p_vol->cache.p_current_fat, p_page);
    }
}

void VFiPFCACHE_FreeDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    if (p_vol->cache.p_current_data != 0) {
        p_page->p_mod_sbuf = PF_NULL;
        p_page->p_mod_ebuf = PF_NULL;
        VFiPFCACHE_DoFreeCachePage(&p_vol->cache.p_current_data, p_page);
    }
}

pf_s32 VFiPFCACHE_ReadFATPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page) {
    pf_s32 err;

    err = VFiPFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_fat, sector, pp_page, 0U);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_ReadDataPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_s32 err;

    err = VFiPFCACHE_DoReadPage(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_ReadDataPageAndFlushIfNeeded(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_bool set_sig) {
    pf_s32 err;

    err = VFiPFCACHE_DoReadPageAndFlushIfNeeded(p_vol, &p_vol->cache.p_current_data, sector, pp_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_ReadDataNumSector(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 0x10;
    }
    err = VFiPFCACHE_DoReadNumSector(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_WriteFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page) {
    pf_s32 err;

    err = VFiPFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_fat, p_page, 0);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_WriteDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page, pf_bool set_sig) {
    pf_s32 err;

    err = VFiPFCACHE_DoWritePage(p_vol, &p_vol->cache.p_current_data, p_page, set_sig);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector) {
    pf_s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 0x10;
    }
    err = VFiPFCACHE_DoWriteSector(p_vol, &p_vol->cache.p_current_fat, p_buf, sector);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success) {
    pf_s32 err;

    if (sector >= p_vol->bpb.total_sectors) {
        return 0x10;
    }
    err = VFiPFCACHE_DoWriteNumSectorAndFreeIfNeeded(p_vol, &p_vol->cache.p_current_data, p_buf, sector, num_sector, p_num_success);
    if (err != 0) {
        return err;
    }
    return 0;
}

PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(PF_VOLUME* p_vol, pf_u32 sector) {
    return VFiPFCACHE_SearchForPage(p_vol, p_vol->cache.p_current_data, sector);
}

pf_s32 VFiPFCACHE_FlushFATCache(PF_VOLUME* p_vol) {
    pf_s32 err;

    err = VFiPFCACHE_DoFlushCache(p_vol, &*p_vol->cache.p_current_fat);
    if (err != 0) {
        return err;
    }
    return 0;
}

pf_s32 VFiPFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, void* signature) {
    pf_s32 err;
    PF_CACHE_PAGE* p_head;
    PF_CACHE_PAGE* p_page;
    pf_u32 check_do_flush;
    pf_u32 do_flush;

    err = 0;
    check_do_flush = 0;
    do_flush = 0;
    if ((p_vol->cache.mode & 7) != 0) {
        p_head = p_vol->cache.p_current_data;
        p_page = p_head;
        if ((p_page->signature == 0) || ((void*)p_page->signature == signature)) {
            if ((p_page != 0) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
                do_flush = 1;
            }
            err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &*p_page);
            if (err != 0) {
                return err;
            }
        }

        for (p_page = p_page->p_next; p_page != p_head; p_page = p_page->p_next) {
            if ((p_page->signature == 0) || ((void*)p_page->signature == signature)) {
                check_do_flush = 0;
                if ((p_page != 0) && ((p_page->stat & 2) != 0) && (p_page->sector != -1)) {
                    check_do_flush = 1;
                }
                err = VFiPFCACHE_FlushPageIfNeeded(p_vol, &*p_page);
                if (err != 0) {
                    if (do_flush != 0) {
                        dCommon_FlushFromVol(p_vol, 0);
                    }
                    return err;
                }
                if (check_do_flush != 0) {
                    do_flush = 1;
                }
                continue;
            }
        }

        if ((do_flush != 0) && (dCommon_FlushFromVol(p_vol, 1) != 0)) {
            return 0x11;
        }
    }

    return err;
}

pf_s32 VFiPFCACHE_FlushAllCaches(PF_VOLUME* p_vol) {
    pf_s32 err;

    err = VFiPFCACHE_DoFlushCache(p_vol, &*p_vol->cache.p_current_fat);
    if (err != 0) {
        return err;
    }
    err = VFiPFCACHE_DoFlushCache(p_vol, &*p_vol->cache.p_current_data);
    if (err != 0) {
        return err;
    }
    return 0;
}

void VFiPFCACHE_FreeAllCaches(PF_VOLUME* p_vol) {
    while ((p_vol->cache.p_current_fat->stat & 1) != 0) {
        VFiPFCACHE_FreeFATPage(p_vol, p_vol->cache.p_current_fat);
    }

    while ((p_vol->cache.p_current_data->stat & 1) != 0) {
        VFiPFCACHE_FreeDataPage(p_vol, p_vol->cache.p_current_data);
    }
}
