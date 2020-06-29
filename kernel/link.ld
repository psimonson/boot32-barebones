ENTRY(kernel_main);
OUTPUT_FORMAT(elf32-i386);
OUTPUT_ARCH(i386:i386);

SECTIONS
{
	. = 0x10000;
	.text : AT(0x0000)
	{
		*(.text);
		*(.data);
		*(.rodata);
		*(.bss);
	}
	/DISCARD/ :
	{
		*(.comment);
		*(.igot.*);
		*(.eh_frame);
	}
}
