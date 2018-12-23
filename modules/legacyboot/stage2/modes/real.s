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
	jnc .error.a20

	; tell the user we enabled the A20 line
	mov si, strings_stage2.enabled_a20
	call info

	; check if our cpu supports long mode and show error messages if result is not support_error_none
	call test_64bit_support

	; if no errors were reported we don't need to compare all
	; the error codes so we jump past them
	cmp al, support_error_none
	je .long_mode_supported

	; error handling for long mode errors
	cmp al, support_error_nocpuid
	je .error.no_cpuid

	cmp al, support_error_noinfo
	je .error.no_info

.long_mode_supported:
	; inform the user long mode is available
	mov si, strings_stage2.long_success
	call info

	; try to enable the SSE
	call enable_sse

	; another error switch statement thing
	cmp al, sse_error_none
	je .sse_succes

	cmp al, sse_error_no_fx
	je .error.no_fx

	cmp al, sse_error_no_sse1
	je .error.no_sse1

	cmp al, sse_error_no_sse2
	je .error.no_sse2

.sse_succes:
	; tell the user sse is enabled
	mov si, strings_stage2.sse_success
	call info

	; return
	ret

.error.a20:
	mov si, strings_stage2.couldnt_enable_a20
	call info
	jmp hang

.error.no_cpuid:
	mov si, strings_stage2.long_no_cpuid
	call info
	jmp hang

.error.no_info:
	mov si, strings_stage2.long_no_info
	call info
	jmp hang

.error.no_fx:
	mov si, strings_stage2.sse_no_fx
	call info
	jmp hang

.error.no_sse1:
	mov si, strings_stage2.sse_no_sse1
	call info
	jmp hang

.error.no_sse2:
	mov si, strings_stage2.sse_no_sse2
	call info
	jmp hang

; stop executing and tell the user we did
hang:
	mov si, strings_stage2.panic
	call info
.loop
	hlt
	jmp .loop