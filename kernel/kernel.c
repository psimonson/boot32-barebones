#include "vga.h"
#include "io.h"

void kernel_main(void)
{
	term_init(BLUE, YELLOW);
	print_char(-1, -1, 'H');
	print_char(-1, -1, 'e');
	print_char(-1, -1, 'l');
	print_char(-1, -1, 'l');
	print_char(-1, -1, 'o');
	print_char(-1, -1, ' ');
	print_char(-1, -1, 'W');
	print_char(-1, -1, 'o');
	print_char(-1, -1, 'r');
	print_char(-1, -1, 'l');
	print_char(-1, -1, 'd');
	print_char(-1, -1, '!');
	print_char(-1, -1, '\n');
}
