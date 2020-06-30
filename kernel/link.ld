ENTRY(kernel_main);
OUTPUT_FORMAT(elf32-i386);
OUTPUT_ARCH(i386:i386);

SECTIONS
{
	. = 0x00010000;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text);
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data);
		*(.rodata);
		*(.bss);
	}
	/DISCARD/ :
	{
		*(.comment);
		*(.eh_frame);
	}
}
