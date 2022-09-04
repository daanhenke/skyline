section .data
gGeneralPurposeRegisterDump:
    dq 4
    dq 4
    dq 8

section .text
global EarlyDumpGeneralPurposeRegisters
EarlyDumpGeneralPurposeRegisters:
    mov [gGeneralPurposeRegisterDump], rax
    mov [gGeneralPurposeRegisterDump + 1], rbx
    mov [gGeneralPurposeRegisterDump + 2], rcx
    mov [gGeneralPurposeRegisterDump + 3], rdx

    mov [gGeneralPurposeRegisterDump + 4], rsi
    mov [gGeneralPurposeRegisterDump + 5], rdi
    mov [gGeneralPurposeRegisterDump + 6], rbp
    mov [gGeneralPurposeRegisterDump + 7], rsp

    mov [gGeneralPurposeRegisterDump + 8], r8
    mov [gGeneralPurposeRegisterDump + 9], r9
    mov [gGeneralPurposeRegisterDump + 10], r10
    mov [gGeneralPurposeRegisterDump + 11], r11
    mov [gGeneralPurposeRegisterDump + 12], r12
    mov [gGeneralPurposeRegisterDump + 13], r13
    mov [gGeneralPurposeRegisterDump + 14], r14
    mov [gGeneralPurposeRegisterDump + 15], r15

    ret

global EarlyGetGeneralPurposeRegistersDump
EarlyGetGeneralPurposeRegistersDump:
    mov rax, gGeneralPurposeRegisterDump
    ret
