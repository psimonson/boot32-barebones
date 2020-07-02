ENTRY(kernel_main);
OUTPUT_FORMAT(elf32-i386);
OUTPUT_ARCH(i386:i386);
BASE_ADDR = 0x00010000;

SECTIONS
{
	.text BASE_ADDR : AT(BASE_ADDR)
	{
		code = .;
		*(.text)
                *(.text.*)
	}
	.rodata : AT(BASE_ADDR + (rodata - code))
	{
		rodata = .;
		*(.rodata)
                *(.rodata.*)
		. = ALIGN(4K);
	}
	.data : AT(BASE_ADDR + (data - code))
	{
		data = .;
		*(.data)
                *(.data.*)
	}
	.bss : AT(BASE_ADDR + (bss - code))
	{
		bss = .;
		*(.bss)
                *(.bss.*)
		*(COMMON)
	}
	/DISCARD/ :
	{
		*(.comment);
		*(.igot.*);
		*(.eh_frame);
	}
}
