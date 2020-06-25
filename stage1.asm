[org 0x7c00]

jmp main
nop

; put BPB here

main:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov bp, 0x9000
	mov sp, bp
	cld

	mov [iBootDrive], dl
	xor ax, ax
	int 0x13

	mov si, op_loading
	call print

	cli
	hlt

%include "common.inc"

op_loading db "Hello world, this is a test.",10,13,0
iBootDrive db 0x00

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55
