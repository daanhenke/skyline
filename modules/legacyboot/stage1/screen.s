; print out the cstring pointed to by register si
printc:
	; save current registers to stack so we dont ruin their values
	pusha
.loop:
	; read out the current byte stored at ram[si] and write it in al then increment si
	lodsb

	; check if we hit a null terminator, jump to .done if we did
	cmp al, 0x00
	je .done

	; call bios function to print ascii char to screen
	mov ah, 0x0E
	mov bx, 0x0000
	int 0x10

	; read next character
	jmp .loop
.done:
	; restore our registers from the stack
	popa
	
	; return
	ret

; print a message with prefix
info:
	; store message on stack
	push si

	; switch statement for prefix
	; default:
	call .stage1

	; case 2:
	cmp byte [es:globals.current_stage], 0x02
	jne .next
	call .stage2
	.next:
	; end of switch statement

	; print prefix
	call printc
	
	; restore message
	pop si

	; print our message
	call printc

	; return
	ret
.stage1:
	mov si, strings_stage1.prefix_stage1
	ret
.stage2:
	mov si, strings_stage1.prefix_stage2
	ret

; print out our panic message then hang
panic:
	; call printc to print our message
	mov si, strings_stage1.panic
	call info
	; hang
.loop:
	jmp .loop