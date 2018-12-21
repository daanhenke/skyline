printc:
	pusha
.loop:
	lodsb

	cmp al, 0x00
	je .done

	mov ah, 0x0E
	mov bx, 0x0000
	int 0x10

	jmp .loop
.done:
	popa
	ret