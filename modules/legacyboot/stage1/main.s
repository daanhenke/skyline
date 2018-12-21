bits 16
org 0

[map all build/stage1.map]

entrypoint:
	jmp stage1.code.segment : stage1_main

%include "include/pointers.s"
%include "stage1/globals.s"
%include "stage1/strings.s"
%include "stage1/screen.s"

panic:
	mov si, strings.panic
	call printc
.loop:
	jmp .loop

stage1_main:
.init:
	cli

	mov ax, cs
	mov ds, ax
	mov fs, ax
	mov gs, ax

	xor ax, ax
	mov ss, ax
	mov sp, stage1.stack.top

	mov es, ax

	sti

	mov byte [es:globals.activeDrive], dl

.message:
	mov si, strings.stage1
	call printc

.read_sector:
	mov ah, 0x02
	mov al, 1
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, [es:globals.activeDrive]
	mov bx, stage1.buffer
	int 0x13

	cmp ah, 0x00
	jne .error

	jmp 0x0000 : stage1.buffer

.done:
	jmp .done

.error:
	call panic