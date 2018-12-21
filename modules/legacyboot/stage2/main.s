bits 16
org 0x9000

[map all build/stage2.map]

stage1_main:
	cli

	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	call panic

panic:
	mov si, strings.stage2
	call printc
.loop:
	jmp .loop

%include "include/pointers.s"
%include "stage1/strings.s"
%include "stage1/screen.s"