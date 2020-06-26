; Global Descriptor Table
gdt:
	dd 0
	dd 0
.code:
	dw 0xffff
	dw 0
	db 0
	db 0x9a
	db 11001111b
	db 0
.data:
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 11001111b
	db 0
.end:

gdt_desc:
	dw gdt.end-gdt-1
	dd gdt

CODE_SEG equ gdt.code-gdt
DATA_SEG equ gdt.data-gdt

