ENTRY(_start)

SECTIONS
{
	. = 0x00009000;

	.text : ALIGN(4K)
	{
		*(.start)
		*(.text)
		*(.rodata*)
	}

	.data : ALIGN(4K)
	{
		*(.data)
	}

	.bss : ALIGN(4K)
	{
		_BSS_START = ABSOLUTE(.);
		*(.bss)
		*(COMMON)
	}
	_BSS_SIZE = ABSOLUTE(.) - _BSS_START;
}