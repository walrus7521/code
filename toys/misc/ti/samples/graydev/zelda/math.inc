;==========================================================
; Math routines
;==========================================================

mul4:
	add a,a
	add a,a
	ld b,0 \ ld c,a
	ret

mul20:
	add a,a
	add a,a
	ld b,a
	add a,a
	add a,a
	add a,b
	ld b,0 \ ld c,a
	ret

wordmul4:
	push hl
	ld h,0 \ ld l,a
	add hl,hl
	add hl,hl
	ld b,h \ ld c,l
	pop hl
	ret

wordmul16:
	push hl
	ld h,0 \ ld l,a
	add hl,hl
	add hl,hl
	add hl,hl
	add hl,hl
	ld b,h \ ld c,l
	pop hl
	ret

wordmul20:
	push hl
	ld h,0 \ ld l,a
	add hl,hl
	add hl,hl
	ld b,h \ ld c,l
	add hl,hl
	add hl,hl
	add hl,bc
	ld b,h \ ld c,l
	pop hl
	ret

hlmul10:
	add hl,hl
	ld b,h \ ld c,l
	add hl,hl
	add hl,hl
	add hl,bc
	ret

