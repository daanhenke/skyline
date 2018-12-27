bits 64

long_main:
	; load the task state segment
	mov ax, gdt.selector.tss
	ltr ax

	; set up our segment registers
	mov ax, gdt.selector.kernel.data
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	xor rax, rax
	xor rbx, rbx
	xor rcx, rcx
	xor rdx, rdx
	xor rdi, rdi
	xor rsi, rsi
	xor rbp, rbp

	xor r8, r8
	xor r9, r9
	xor r10, r10
	xor r11, r11
	xor r12, r12
	xor r13, r13
	xor r14, r14
	xor r15, r15


	mov rsp, stage3.stack.main.top
    
    jmp 0x20000