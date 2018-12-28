#include "page.h"
#include "types.h"
#include "memory.h"
#include "std/memset.h"

static u64 page_memory_pointer = MEMORY_PAGETABLE_REST;

u64 get_page_address() {
    memzero(page_memory_pointer, PAGE_SIZE_SMALL);
    page_memory_pointer += PAGE_SIZE_SMALL;
    return page_memory_pointer - PAGE_SIZE_SMALL;
}

void page_map_page(u64 virtual_address, u64 physical_address, u32 page_flags) {
    u64 *pml4t = (u64 *) PML4T_ADDRESS;

    u32 pml4t_entry = INDEX_PML4T(virtual_address);
    u32 pdpt_entry = INDEX_PDPT(virtual_address);
    u32 pdt_entry = INDEX_PDT(virtual_address);
    u32 pt_entry = INDEX_PT(virtual_address);

    // Check if we have an existing entry in the pml4t, if not create it
    if (pml4t[pml4t_entry] == 0) {
        u64 addr = get_page_address();
        pml4t[pml4t_entry] = addr | PF_PRESENT | PF_RW;
    }

    u64 *pdpt = (u64 *) INDEX_TO_ADDRESS(pml4t[pml4t_entry]);
    if (pdpt[pdpt_entry] == 0) {
        u64 addr = get_page_address();
        pdpt[pdpt_entry] = addr | PF_PRESENT | PF_RW;
    }

    u64 *pdt = (u64 *) INDEX_TO_ADDRESS(pdpt[pdpt_entry]);
    if (pdt[pdt_entry] == 0) {
        u64 addr = get_page_address();
        pdt[pdt_entry] = addr | PF_PRESENT | PF_RW;
    }

    u64 *ptt = (u64 *) INDEX_TO_ADDRESS(pdt[pdt_entry]);
    ptt[pt_entry] = physical_address | page_flags;
}