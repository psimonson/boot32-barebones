load_gdt:
	cli
	pusha
	lgdt [gdt_desc]
	sti
	popa
	ret

; Global Descriptor Table
gdt:
	dd 0
	dd 0
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
.end:

gdt_desc:
	dw gdt.end-gdt-1
	dd gdt+0x10000
