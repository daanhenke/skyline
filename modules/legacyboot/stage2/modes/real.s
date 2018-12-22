bits 16

real_main:
	; disable software interrupts
	cli

	; set ax to 0 and use it to clear all section registers
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; set stage for screen.s:info prefix
	mov byte [es:globals.current_stage], 0x02

	; tell the user we're in stage2
	mov si, strings_stage2.start_message
	call info