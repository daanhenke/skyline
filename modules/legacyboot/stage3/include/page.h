#pragma once
#include "types.h"

#define PAGE_SIZE_SMALL 0x1000
#define PAGE_SIZE_LARGE 0x200000
#define PAGE_SIZE_HUGE 0x40000000

#define PML4T_ADDRESS 0xFFFFFFFFFFFFF000

#define PF_PRESENT      (1 << 0)
#define PF_RW           (1 << 1)
#define PF_USER         (1 << 2)
#define PF_WRITETHRU    (1 << 3)
#define PF_DCACHE       (1 << 4)
#define PF_ACCESS       (1 << 5)
#define PF_DIRTY        (1 << 6)
#define PF_PAGESIZE     (1 << 7)
#define PF_GLOBALCACHE  (1 << 8)
#define PF_SYSTEM       (1 << 9)

#define INDEX_PML4T(address) (((address) >> 39) & 0x1ff)
#define INDEX_PDPT(address) (((address) >> 30) & 0x1ff)
#define INDEX_PDT(address) (((address) >> 21) & 0x1ff)
#define INDEX_PT(address) (((address) >> 12) & 0x1ff)
#define INDEX_TO_ADDRESS(index) ((index) & ~0x3ff)

void page_map_page(u64 virtual_address, u64 physical_address, u32 page_flags);