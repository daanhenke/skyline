page_directory_entry:
	.present          equ 1 << 0
	.read_write       equ 1 << 1
	.user_supervisor  equ 1 << 2
	.write_trough     equ 1 << 3
	.cache_disabled   equ 1 << 4
	.accessed         equ 1 << 5
	.page_size        equ 1 << 6
	.ignored          equ 1 << 7

page_table_entry:
	.present          equ 1 << 0
	.read_write       equ 1 << 1
	.user_supervisor  equ 1 << 2
	.write_trough     equ 1 << 3
	.cache_disabled   equ 1 << 4
	.accessed         equ 1 << 5
	.dirty            equ 1 << 6
	.pat_memory_type  equ 1 << 7
	.global           equ 1 << 8

; will setup our page tables and load the pml4t into cr3
page_load:
	; store our segment register so we can restore it later
	push es

	; set our segment register to the start of page table ram
	mov ax, stage2.page_table >> 4
	mov es, ax

	; clear all RAM used for paging
	cld
	xor eax, eax
	xor edi, edi
	mov ecx, (stage2.page_table.end - stage2.page_table) >> 2
	rep stosd

	; this is where we start setting up our page tables
	; we set up a very basic layout that allows our stage3
	; to load and modify it to it's hearts content

	; set pml4t[0] to the start of our pdpt
	mov di, stage2.page_table.pml4t & 0xFFFF
	mov dword [es:di], stage2.page_table.pdpt | page_table_entry.present | page_table_entry.read_write

	; set pdpt[0] to the start of our pdt
	mov di, stage2.page_table.pdpt & 0xFFFF
	mov dword [es:di], stage2.page_table.pdt | page_table_entry.present | page_table_entry.read_write

	; use pdt[0] to map the first 2MiB of ram using 4KiB pages
	mov di, stage2.page_table.pdt & 0xFFFF
	mov dword [es:di + 0x00], stage2.page_table.pt | page_table_entry.present | page_table_entry.read_write

	; use pdt[1:5] to map the next 8MiB of RAM using large pages (2MiB)
	mov dword [es:di + 0x08], 0x00200000 | page_table_entry.pat_memory_type | page_table_entry.present | page_table_entry.read_write
	mov dword [es:di + 0x10], 0x00400000 | page_table_entry.pat_memory_type | page_table_entry.present | page_table_entry.read_write
	mov dword [es:di + 0x18], 0x00600000 | page_table_entry.pat_memory_type | page_table_entry.present | page_table_entry.read_write
	mov dword [es:di + 0x20], 0x00800000 | page_table_entry.pat_memory_type | page_table_entry.present | page_table_entry.read_write

	; now we need to set up the page table pointed to by pdt[0]
	; we do this using a little loop which will write 512 page table entries
	mov di, stage2.page_table.pt & 0xFFFF
	mov eax, page_table_entry.present | page_table_entry.read_write
	mov cx, 512
.page_loop:
	mov [es:di], eax
	add eax, 0x1000
	add di, 0x08
	loop .page_loop

	; disable cache on video RAM so our updates are actually put on screen
	mov edi, stage2.video
	mov cx, 32
	call page_mark_nocache

	; enable page tables by writing our parent table to cr3
	mov edi, stage2.page_table
	mov cr3, edi

	; enable the PAE extension
	mov eax, cr4
	or eax, (1 << 5)
	mov cr4, eax

	; restore es and return
	pop es
	ret

page_mark_nocache:
	shr edi, 9
	add edi, stage2.page_table.pt & 0xFFFF
.loop:
	mov eax, [es:di]
	or eax, page_table_entry.cache_disabled | page_table_entry.write_trough | page_table_entry.pat_memory_type
	mov [es:di], eax
	add di, 8
	loop .loop

	ret