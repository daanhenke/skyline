stage2.stack.top equ 0x7C00
stage2.gdt       equ 0x3000
stage2.tss       equ 0x3100

stage2.video equ 0x000A0000

stage2.page_table          equ 0x00010000
stage2.page_table.pml4t    equ 0x00010000
stage2.page_table.pdpt     equ 0x00011000
stage2.page_table.pdt      equ 0x00012000
stage2.page_table.pt       equ 0x00013000
stage2.page_table.end      equ 0x00020000

stage3.stack.interrupt.top equ 0x001FF000
stage3.stack.nmi.top       equ 0x0008C000
stage3.stack.df.top        equ 0x0008E000
stage3.stack.mc.top        equ 0x00090000
stage3.stack.main.top      equ 0x00300000
stage3.stack.main.bottom   equ 0x00200000