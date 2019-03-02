;==========================================================
; Map routines
;==========================================================

;==========================================================
; mapCheckLargePos
;==========================================================
; b=x, c=y
; d=width  (16 pixels is 2)
; e=height (idem)
; output: a=(wrong) tile nr
mapCheckLargePos:

	xor a
mclp_yloop:
	ld (mclp_y),a
	add a,c
	ld l,a
	
	xor a
mclp_xloop:
	ld (mclp_x),a
	add a,b
	ld h,a

	push bc
	push hl
	call mapCheckpos
	pop hl
	pop bc
	ld (mclp_outcome),a
	cp 32 \ jr nc,mclp_end
	;jr mclp_end

	ld a,(mclp_x)
	inc a
	cp d \ jr nz,mclp_xloop
	ld a,(mclp_y)
	inc a
	cp e \ jr nz,mclp_yloop
mclp_end:
	ld a,(mclp_outcome)
	ret
	
mclp_x: .db 0 ;ugly, couldnt find another method
mclp_y:	.db 0
mclp_outcome:	.db 0
;==========================================================
; mapCheckPos
;==========================================================
; h=x, l=y
; output: a=tile
mapCheckpos:
	ld a,h
	push af
	ld h,0
	add hl,hl
	add hl,hl
	ld b,h \ ld c,l
	add hl,hl
	add hl,hl
	add hl,bc
	pop af
	ld b,0 \ ld c,a
	add hl,bc
	ld bc,submap
	add hl,bc
	ld a,(hl)

	ret

;==========================================================
; mapDrawView
;==========================================================
; draw the player view
mapDrawView:


	;jp mdvend

	;first update the tiles
	ld hl,submap
	ld b,16
mdv_updyloop:
	push bc
	ld b,20
mdv_updxloop:
	push bc
	ld a,(hl)
	cp 16 \ jr c,mdv_updend
	cp 28 \ jr nc,mdv_updend
	inc a
	cp 20 \ jr z,mdv_updrst
	cp 24 \ jr z,mdv_updrst
	cp 28 \ jr z,mdv_updrst
	jr mdv_updend
mdv_updrst:
	sub 4
mdv_updend:
	ld (hl),a
	inc hl
	pop bc
	djnz mdv_updxloop
	pop bc
	djnz mdv_updyloop

mdvend:

	ld hl,submap
	ld a,(viewX)
	ld b,0 \ ld c,a
	add hl,bc
	
	ld a,(viewY)
	call wordmul20
	add hl,bc

	ex de,hl

	xor a
mdv_yloop:
	ld (y),a
	xor a
mdv_xloop:
	ld (x),a

	ld a,(de) ;de=submap
	push de
	call wordmul16
	ld hl,tiles1
	add hl,bc
	push hl
	pop ix

	ld a,(y)
	add a,a
	add a,a
	add a,a
	ld l,a

	ld a,(x)
	call gsAlignedSprite

	pop de
	inc de	

	ld a,(x)
	inc a
	cp 10 \ jr nz,mdv_xloop

	ld bc,10
	ex de,hl
	add hl,bc
	ex de,hl

	ld a,(y)
	inc a
	cp 8 \ jr nz,mdv_yloop
	ret


;==========================================================
; mapCreateSubMap
;==========================================================
; this creates the submap

mapCreatesubmap:

	ld a,(superMapY)

	ld h,0
	ld l,a
	add hl,hl ;*2
	add hl,hl ;*4
	add hl,hl ;*8
	add hl,hl ;*16
	add hl,hl ;*32
	push hl
	add hl,hl ;*64
	push hl
	add hl,hl ;*128
	push hl
	add hl,hl ;*256
	pop de
	add hl,de ;*384
	pop de
	add hl,de ;*448
	pop de
	add hl,de ;*480

	ld d,h \ ld e,l
	ld a,(superMapX)
	ld h,0 \ ld l,a

	call hlmul10

	add hl,de
	ld de,map0
	add hl,de

	;ld hl,map0+(4*480+(2*10))

	ld de,submap
	ld b,8
mapCS_yloop:
	push bc
	ld b,10
mapCS_xloop:
	push bc

	ld a,(hl)
	push hl
	call wordmul4
	ld hl,convert
	add hl,bc
	ld a,(hl)
	ld (de),a
	inc hl
	inc de
	push de
	ld a,(hl)
	ld (de),a
	ex de,hl
	ld bc,19
	add hl,bc
	ex de,hl
	inc hl
	ld a,(hl)
	ld (de),a
	inc hl
	inc de
	ld a,(hl)
	ld (de),a
	pop de
	inc de
	pop hl
	inc hl
mapCS_xend:
	pop bc
	djnz mapCS_xloop
	ex de,hl
	ld bc,20
	add hl,bc
	ex de,hl
	ld bc,50
	add hl,bc
mapCS_yend:
	pop bc
	djnz mapCS_yloop

	ret
