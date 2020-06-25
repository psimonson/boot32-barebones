; all common functions for 16 bit and 32 bit
; by Philip R. Simonson
; ==========================================

; [ds:si] = message to print.
; ================================
print:
	pusha
.loop:
	lodsb		; load a byte into al
	or al, al ; check al if 0
	jz .done ; jump to done
	mov ah, 0x0e
	mov bh, 0x00
	int 0x10
	jmp short .loop
.done:
	popa
	ret
