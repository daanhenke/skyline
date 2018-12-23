sse_error_none     equ 0x00
sse_error_no_fx    equ 0x01
sse_error_no_sse1  equ 0x02
sse_error_no_sse2  equ 0x03

; enables the SSE so we can do floating point operations
enable_sse:
	; get our cpu feature flags into ecx & edx
	mov eax, 0x01
	cpuid

	; check if cpu supports FXSAVE / FXRSTOR
	test edx, (1 << 24)
	jz .errors.no_fx

	; check if cpu supports SSE1
	test edx, (1 << 25)
	jz .errors.no_sse1

	; check if cpu supports SSE2
	test edx, (1 << 26)
	jz .errors.no_sse2

	; enable FPU (floating point unit) with monitoring
	; we turn off bit 2 (EM bit)
	; we turn on it 1   (monitor bit)
	mov eax, cr0
	and eax, ~(1 << 2)
	and eax, (1 << 1)

	; make sure FXSAVE/FXRSTOR will save the content of our FPU
	; enable the use of SSE instructions & indicate that our kernel
	; will handle floating point exceptions
	mov eax, cr4
	or eax, (1 << 9) | (1 << 10)
	mov cr4, eax

	; set status code to signify success
	mov ah, sse_error_none
.done:
	ret

.errors.no_fx:
	mov ah, sse_error_no_fx
	jmp .done

.errors.no_sse1:
	mov ah, sse_error_no_sse1
	jmp .done

.errors.no_sse2:
	mov ah, sse_error_no_sse2
	jmp .done