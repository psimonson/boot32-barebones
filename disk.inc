; simple BIOS disk services

; ======================================
; reset disk drive
; ======================================
reset_disk:
	push ax
	xor ax, ax
	mov dl, [iBootDrive]
	int 0x13
	pop ax
	ret

; ======================================
; ax = count of sectors to read
; cl = start sector to read
; [es:bx] = buffer address pointer
; ======================================
read_disk:
	pusha
	mov di, 5
.loop:
	push ax
	push bx
	mov ah, 0x02
	mov al, 0x01
	mov ch, 0x00
	mov dh, 0x00
	mov dl, [iBootDrive]
	pop bx
	int 0x13
	jc .fail
	pop ax
	cmp ax, 0
	jne .good
	mov si, op_fdone
	call print
	popa
	ret
.good:
	inc cl
	add bx, 512
	dec ax
	mov si, op_progress
	call print
	jmp short .loop
.fail:
	clc
	xor ax, ax
	int 0x13
	dec di
	cmp di, 0
	jne .loop
	mov si, op_ferror
	call print
	ret
