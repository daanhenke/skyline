; task state segment
; contains info used during privilege mode changes
struc tss
	.reserved1 resd 1 ; reserved
	.rsp0      resq 1 ; stack pointer for ring 0
	.rsp1      resq 1 ; stack pointer for ring 1
	.rsp2      resq 1 ; stack pointer for ring 2
	.reserved2 resq 1 ; reserved
	.ist1      resq 1 ; interrupt stack table pointers 1 trough 7
	.ist2      resq 1
	.ist3      resq 1
	.ist4      resq 1
	.ist5      resq 1
	.ist6      resq 1
	.ist7      resq 1
	.reserved3 resq 1 ; reserved
	.reserved4 resw 1 ; reserved
	.iobp      resw 1 ; I/O permissions bitmap offset
endstruc

align 8
tss.entry:
	istruc tss
		at tss.rsp0, dq stage3.stack.interrupt.top
		at tss.rsp1, dq 0
		at tss.rsp2, dq 0
		at tss.ist1, dq stage3.stack.nmi.top
		at tss.ist2, dq stage3.stack.df.top
		at tss.ist3, dq stage3.stack.mc.top
		at tss.ist4, dq 0
		at tss.ist5, dq 0
		at tss.ist6, dq 0
		at tss.ist7, dq 0
		at tss.iobp, dw tss_size
	iend
tss.entry.size equ ($ - tss.entry)

; copies the TSS to where it needs to go and returns
tss_load:
	mov si, tss.entry
	mov di, stage2.tss
	mov cx, tss.entry.size
	shr cx, 1
	rep movsw
	ret