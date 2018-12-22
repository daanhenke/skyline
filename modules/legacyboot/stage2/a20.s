bits 16

; enable the A20 address line so we can access memory above 1mb
enable_upper_memory:
	; save registers to stack
	pusha

	; check if we already have access to upper memory
	call test_upper_memory
	jc .done

	; attempt using FAST A20
	in al, 0x92
	or al, 2
	out 0x92, al
	xor ax, ax

	call test_upper_memory
	jc .done

	; attempt using the BIOS
	mov ax, 0x2401
	int 0x15

	call test_upper_memory
	jc .done

	; if we haven't enabled the A20 line by now we're screwed
	; could implement enabling it using the keyboard controller
	; if this ever becomes an issue

.done:
	; restore registers & return
	popa
	ret

; check if we have access to upper memory
test_upper_memory:
	; save general purpose registers + es and ds on the stack
	pusha
	push ds
	push es

	; unset carry bit to signify failure
	clc

	; due to the way memory is accessed in real mode multiple "addresses"
	; can point to the same physical address
	; the physical address for [es:si] would be calculated like so:
	;   address = es * 16 + si
	; we can use this to our advantage to detect if we have access past address 0xffff
	; this is because we can craft two addresses which will point to the same
	; physical address if the A20 line would be disabled like so:
	;	address_low  = 0x0000 * 16 + 0x0000 = 0x00000000 & 0xFFFF = 0x0000
	;	address_high = 0xffff * 16 + 0x0001 = 0x00010000 & 0xFFFF = 0x0000
	; if the A20 line is enabled the upper 16 bits would not be cut off, resulting in
	; these two addresses being different

	; clear ax so we can set es to 0x0000
	xor ax, ax
	mov es, ax

	; not ax (0x0000 -> 0xffff) so we can set ds to 0xffff
	not ax
	mov ds, ax

	; set si and di to their values for the comparisant
	mov si, 0x0000
	mov di, 0x0001

	; temporily store the values of the memory we're about to play with
	; on the stack so we can restore them later
	mov ax, [es:si]
	push ax

	mov ax, [ds:di]
	push ax

	; write different values to the locations of [es:si] and [ds:di] respectively
	mov byte [es:si], 0xAA
	mov byte [ds:di], 0xBB

	; check if es:si is 0xBB, if it is then [ds:di] and [es:si] point
	; to the same physical address and the A20 is disabled
	cmp byte[es:si], 0xBB

	; restore values of [es:si] and [ds:di] from stack
	pop ax
	mov [es:si], ax

	pop ax
	mov [ds:di], ax

	; if byte[es:si] was 0xBB, we skip setting the carry flag
	; to signify the A20 line is disabled
	je .done

	; set the carry flag to tell function caller the A20 line is enabled
	stc

.done:
	; restore our registers and return
	pop ds
	pop es
	popa

	ret