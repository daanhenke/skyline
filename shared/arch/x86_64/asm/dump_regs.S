section .text

global GetStackRegisters
GetStackRegisters:
    mov [rcx], rbp
    mov [rcx + 1], rsp
    ret

global GetInstructionPointer
GetInstructionPointer:
    mov rax, [rsp]
    ret
