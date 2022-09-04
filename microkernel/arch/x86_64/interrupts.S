section .text

extern InterruptHandler

global gInterruptHandlerStubs
gInterruptHandlerStubs:

.int0:
    push 0
    push 0
    jmp InterruptHandler
    pop rax
    pop rax
    ret

.int1:
    push 0
    push 1
    jmp InterruptHandler
    pop rax
    pop rax
    ret
