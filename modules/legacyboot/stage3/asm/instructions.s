bits 64

global disable_interrupts
global enable_interrupts

global inb
global outb
global inw
global outw
global ind
global outd

disable_interrupts:
	cli
	ret

enable_interrupts:
	sti
	ret

inb:
	mov dx, di
	xor rax, rax
	in al, dx
	ret

outb:
	mov dx, di
	mov ax, si
	out dx, al
	ret

inw:
	mov dx, di
	xor rax, rax
	in ax, dx
	ret

outw:
	mov dx, di
	mov ax, si
	out dx, ax 
	ret

ind:
	mov dx, di
	xor rax, rax
	in eax, dx
	ret

outd:
	mov dx, di
	mov eax, esi
	out dx, eax
	ret