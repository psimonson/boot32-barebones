; dummy IDT
idt:
	dw 0
	dw 0
	db 0
	db 0
	dw 0
	dd 0
	dd 0
.pointer:
	dw $-idt-1
	dd idt

