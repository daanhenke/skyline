stage1.code.address equ 0x7C00
stage1.code.segment equ stage1.code.address >> 4

stage1.stack.top equ stage1.code.address

stage1.buffer_stage2 equ 0x8000
stage1.buffer_stage3 equ 0x9000

stage1.globals equ 0x3000