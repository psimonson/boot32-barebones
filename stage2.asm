; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x0]

start:
	call a20_bios
	call check_a20

	mov si, op_pmode
	call print

;	cli
;	lgdt [gdtr]
;	mov eax, cr0
;	or al, 1
;	mov cr0, eax
;	sti

	mov si, op_pmode2
	call print

	cli
	hlt

%include "common.inc"
%include "a20.inc"

op_pmode db "Entering protected mode...",0
op_pmode2 db "done!",13,10,0
op_a20yes db "A20 is enabled.",13,10,0
op_a20no db "A20 is disabled.",13,10,0

; gdt stuff below
gdt_start:
	dw 0
	dw 0
gdt_code:
	dw 0xffff
	db 0
	db 0x9a
	db 0xcf
	db 0
gdt_data:
	dw 0xffff
	db 0
	db 0x92
	db 0xcf
	db 0
gdt_end:

gdtr:
	dw gdt_end-gdt_start-1
	dq gdt_start

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start
