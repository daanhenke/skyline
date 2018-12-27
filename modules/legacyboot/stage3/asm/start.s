bits 64

section .start
	global _start

	extern stage3_main

	extern _BSS_START
	extern _BSS_SIZE

_start:
	cld

	mov rdi, _BSS_START
	mov rsi, _BSS_SIZE
	call memzero

	call stage3_main
.loop:
	cli
	hlt
	jmp .loop

memzero:
	xor rax, rax
	mov rcx, rsi
	rep stosb

	ret