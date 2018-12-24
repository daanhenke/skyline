bits 64

long_main:
	;long = 6c6f6e67
	mov rax, 0x2f672f6e2f6f2f6c
    mov qword [0xb8000], rax

    ;mode = 6d6f6465
    mov rax, 0x2f652f642f6f2f6d
    mov qword [0xb8008], rax
    hlt