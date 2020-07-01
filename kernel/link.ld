ENTRY(kernel_main);
OUTPUT_FORMAT(elf32-i386);
OUTPUT_ARCH(i386:i386);

SECTIONS
{
	. = 0x00080000;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text);
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata);
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data);
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.bss);
		*(COMMON);
	}
	/DISCARD/ :
	{
		*(.comment);
		*(.eh_frame);
	}
}
