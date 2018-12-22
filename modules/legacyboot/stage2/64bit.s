support_error_none    equ 0x00
support_error_nocpuid equ 0x01

; will check if our cpu supports long mode, sets ah with the status
test_64bit_support:
	; check if our cpu supports the cpuid opcode, if not long mode is not supported
	call has_cpuid
	jnc .error.no_cpuid

	; set our status to success and return
	mov ah, support_error_none
	ret

.error.no_cpuid:
	; set our status to support_error_nocpuid and return
	mov ah, support_error_nocpuid
	ret

; will set carry bit if cpuid is supported
has_cpuid:
	; save used registers
	push eax
	push ecx

	; we can check if cpuid is supported by seeing if
	; bit 21 (the ID bit) survives a popfd & pushfd

	; copy flags to both registers
	pushfd
	pop eax
	mov ecx, eax

	; set flag 21 and put them back on the stack
	xor eax, (1 << 21)
	push eax

	; pop the flags back off the stack
	popfd

	; get flags back into eax, if cpuid is supported
	; flag 21 should still be 1
	pushfd
	pop eax

	; restore the original flags from ecx
	push ecx
	popfd

	; unset carry flag to signify failure
	clc

	; check if eax is equal to ecx, if so flag 21 hasn't changed and we should
	; indicate failure by not setting the carry flag
	xor eax, ecx
	jz .done

	stc

.done:
	; restore used registers and return
	pop ecx
	pop eax

	ret