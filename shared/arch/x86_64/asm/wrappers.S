section .text

global _test
_test:
    mov rax, 1337
    ret

global _hlt
_hlt:
    hlt
    jmp _hlt
