ENTRY(kernel_main);
OUTPUT_FORMAT(elf32-i386);
OUTPUT_ARCH(i386:i386);
BASE_ADDR = 0x00100000;

SECTIONS
{
	.text BASE_ADDR : AT(BASE_ADDR)
	{
		code = .;
		*(.text)
		*(.rodata)
		. = ALIGN(4K);
	}
	.data : AT(BASE_ADDR + (data - code))
	{
		data = .;
		*(.data)
		. = ALIGN(4K);
	}
	.bss : AT(BASE_ADDR + (bss - code))
	{
		bss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4K);
	}
	/DISCARD/ :
	{
		*(.comment);
		*(.igot.*);
		*(.eh_frame);
	}
}
