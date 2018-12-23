stage2.stack.top equ 0x7C00
stage2.gdt       equ 0x3000
stage2.tss       equ 0x3100

stage3.stack.interrupt.top equ 0x001ff000
stage3.stack.nmi.top       equ 0x0008c000
stage3.stack.df.top        equ 0x0008e000
stage3.stack.mc.top        equ 0x00090000