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

	; initialize stack pointer
	mov sp, stage2.stack.top

	; clear all general purpose registers
	xor bx, bx
	xor cx, cx
	xor dx, dx
	xor si, si
	xor di, di
	xor bp, bp

	; set stage for screen.s:info prefix
	mov byte [es:globals.current_stage], 0x02

	; tell the user we're in stage2
	mov si, strings_stage2.start_message
	call info

	; enable A20 line so we can have more than one MiB of ram
	call enable_upper_memory

	; check if we enabled it
	call test_upper_memory
	jnc error_a20

	; tell the user we enabled the A20 line
	mov si, strings_stage2.enabled_a20
	call info

	; return
	ret

error_a20:
	mov si, strings_stage2.couldnt_enable_a20
	call info
	jmp hang

hang:
	jmp hang