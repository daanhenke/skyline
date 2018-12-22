bits 16
org 0

[map all build/stage1.map]

entrypoint:
	; far jump to our code so we update the cs
	jmp stage1.code.segment : stage1_main

stage1_main:
	; disable softawre interrupts
	cli

	; set all segment registers to the current code segment
	mov ax, cs
	mov ds, ax
	mov fs, ax
	mov gs, ax

	; clear ax
	xor ax, ax

	; set up our stack
	mov ss, ax
	mov sp, stage1.stack.top

	; clear es, so we can use it to access the first 64kb of RAM
	mov es, ax

	; reenable software interrupts
	sti

	; store the current active drive for later
	mov byte [es:globals.active_drive], dl

	; set stage for screen.s:info prefix
	mov byte [es:globals.current_stage], 1

	; print out a status message
	mov si, strings_stage1.start_message
	call info

	; tell the user we're loading stage2 from the active hdd
	mov si, strings_stage1.load_message
	call info

	; read the stage2 sectors from our active hdd
	mov ah, 0x02
	mov al, 9
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, [es:globals.active_drive]
	mov bx, stage1.buffer
	int 0x13
	
	; check if the read was succesful
	cmp ah, 0x00
	jne .error

	; tell the user we're jumping to stage2
	mov si, strings_stage1.jump_message
	call info

	; jump to our stage2
	jmp 0x0000 : stage1.buffer

.error:
	; display error message
	call panic

%include "include/pointers.s"
%include "stage1/globals.s"
%include "stage1/strings.s"
%include "stage1/screen.s"