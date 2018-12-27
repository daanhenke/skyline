; a descriptor in the global descriptor table
; every descriptor is 8 bytes long and stores the following data

; bits:
; 0:15   limit bits 0:15
; 16:31  base address bits 0:15
; 32:39  base address bits 16:23
;    40  accessed bit
;    41  readable / writable bit
;    42  direcction bit
;    43  executable bit
;    44  must be 1 for descriptor to be valid
; 45:46  privilege level (ring 0 = most privilege, ring 3 = least privileged)
;    47  present bit
; 48:51  limit bits 16:19
;    52  must be 1 for descriptor to be valid
;    53  long mode flag
;    54  size bit (0 = 16-bit, 1 = 32-bit)
;    55  granularity bit (0 = 1B, 1=4KiB)
; 56:63  base address bits 24:31
struc gdt.descriptor
	.limit_low:        resw 1
	.base_low:         resw 1
	.base_middle:      resb 1
	.access:           resb 1
	.limit_high_flags: resb 1
	.base_high:        resb 1
endstruc

; very similar to a gdt descriptor, but with two more fields
; one dword being used to extend base address past 32bits
; and one reserved dword
struc tss.descriptor
	.limit_low:        resw 1
	.base_low:         resw 1
	.base_middle:      resb 1
	.access:           resb 1
	.limit_high_flags: resb 1
	.base_high:        resb 1
	.base_highest:     resd 1
	.reserved:         resd 1
endstruc

align 8
gdt.table:
	; null descriptor
	istruc gdt.descriptor
		at gdt.descriptor.limit_low,        dw 0x0000
		at gdt.descriptor.base_low,         dw 0x0000
		at gdt.descriptor.base_middle,      db 0x00
		at gdt.descriptor.access,           db 00000000b
		at gdt.descriptor.limit_high_flags, db 00000000b
		at gdt.descriptor.base_high,        db 0x00
	iend

	; stage3 data segment
	istruc gdt.descriptor
		at gdt.descriptor.limit_low,        dw 0x0000
		at gdt.descriptor.base_low,         dw 0x0000
		at gdt.descriptor.base_middle,      db 0x00
		at gdt.descriptor.access,           db 10010010b
		at gdt.descriptor.limit_high_flags, db 00000000b
		at gdt.descriptor.base_high,        db 0x00
	iend

	; stage3 code segment
	istruc gdt.descriptor
		at gdt.descriptor.limit_low,        dw 0x0000
		at gdt.descriptor.base_low,         dw 0x0000
		at gdt.descriptor.base_middle,      db 0x00
		at gdt.descriptor.access,           db 10011010b
		at gdt.descriptor.limit_high_flags, db 00100000b
		at gdt.descriptor.base_high,        db 0x00
	iend

	; tts descriptor
	istruc tss.descriptor
		at tss.descriptor.limit_low,        dw tss_size - 1
		at tss.descriptor.base_low,         dw stage2.tss & 0xFFFF
		at tss.descriptor.base_middle,      db (stage2.tss >> 16) & 0xFF
		at tss.descriptor.access,           db 10001001b
		at tss.descriptor.limit_high_flags, db 00000000b
		at tss.descriptor.base_high,        db (stage2.tss >> 24) & 0xFF
		at tss.descriptor.base_highest,     dd (stage2.tss >> 32)
		at tss.descriptor.reserved,         dd 0x00000000
	iend
gdt.table.size equ ($ - gdt.table)

; store the limit (offset of last byte) of our gdt and the actual pointer to our gdt
gdt.table.pointer:
	dw gdt.table.size - 1
	dq stage2.gdt

gdt.selector:
	.kernel.data equ 0x08
	.kernel.code equ 0x10
	.tss         equ 0x18

; copies the GDT to where it needs to go and returns
gdt_load:
	mov si, gdt.table
	mov di, stage2.gdt
	mov cx, gdt.table.size
	shr cx, 1
	rep movsw
	ret