; Global Descriptor Table
gdt:
.null: equ $-gdt
	dd 0
	dd 0
.code: equ $-gdt
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
.data: equ $-gdt
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
.pointer:
	dw $-gdt-1
	dd gdt
