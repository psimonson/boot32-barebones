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

; ==================================================
; Description: Load file from disk using LBA.
; ax - LBA (Logical Block Address)
; cx - Number of sectors to read.
; [es:bx] - Location to store at (in memory).
; ==================================================
read_disk:
	mov di, 5
.loop:
	push ax
	push cx
	push bx
	; calculate sector
	mov bx, word [iTrackSect]
	xor dx, dx
	div bx
	inc dx
	mov cl, dl
	; calculate track/head
	mov bx, word [iHeadCnt]
	xor dx, dx
	div bx
	mov ch, al
	xchg dl, dh
	; read sector
	mov ax, 0x0201
	mov dl, byte [iBootDrive]
	pop bx
	int 0x13
	jnc .success
	xor ax, ax
	int 0x13
	dec di
	pop cx
	pop ax
	cmp di, 0
	jne .loop
	mov si, op_failed
	call print
	jmp $
.success:
	mov si, op_progress
	call print
	pop cx
	pop ax
	inc ax
	add bx, word [iSectSize]
	loop read_disk
	mov si, op_done
	call print
	ret
