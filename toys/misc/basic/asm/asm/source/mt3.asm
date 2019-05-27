;-----------------------------------------
;
;		mobileTunes 3
;		  by Kerm Martian
;
;-----------------------------------------
.nolist
#include "dcs6.inc"
#include "keyval.inc"
OpenFileFlag	.equ AppBackupScreen+94		;byte
FilePtr	.equ AppBackupScreen+95		;word
FileSize	.equ AppBackupScreen+97		;word
OffsetTable .equ	AppBackupScreen+99	;word
OffsetSection .equ AppBackupScreen+101	;word
SongNoteLength .equ AppBackupScreen+103	;word
SongNoteCurrent .equ AppBackupScreen+105	;word
bPort .equ 0
MouseY	.equ	$989E	; [header.asm:141]
MouseX	.equ	$989F	; [header.asm:142]

.list
	.org progstart
	.db $BB,$6D
INIT:
	xor d
	.db $C9
	jr Start
	.dw $0000
	.db $06,$00
	.dw Icon
	.dw $0000
	.dw Apstart			;the routine to open files.
	.db $31,$7F			;argh, this be an APMain
	.db $02				;number of accepted filetypes
MyType1:
	.db 0,1,4			;plaintext
Icon:
	.db $07,$E0,$1C,$38,$32,$0C,$75,$0E,$48,$D6,$EC,$73,$D4,$2F,$AC,$17
	.db $D8,$1D,$FC,$2F,$FC,$7F,$7C,$FE,$7D,$FE,$3F,$FC,$1F,$F8,$07,$E0
APIcon:
	.db $3F,$F0,$20,$18,$20,$14,$20,$1E,$3E,$02,$57,$02,$EA,$82,$A5,$82
	.db $E3,$82,$E7,$82,$EF,$82,$7F,$02,$3E,$02,$20,$02,$20,$02,$3F,$FE
Start:
	xor a
	ld (OpenFileFlag),a
	ld hl,0
	ld (FilePtr),hl
	ld (FileSize),hl
	call SetupGUI
MainMouse:
	ld hl,MouseHook
	call GUIMouse
MouseHook:
	ld a,$ff
	out (1),a
	nop \ nop 
	ld a,KeyRow_Top
	out (1),a
	nop \ nop
	in a,(1)
	cp dkY
	jr z,MouseHookPlayPause
	cp dkWindow
	jr z,MouseHookStop
	cp dkGraph
	jr z,MouseHookOpen
	ld a,$ff
	out (1),a
	nop \ nop 
	ld a,KeyRow_5
	out (1),a
	nop \ nop
	in a,(1)
	cp dkClear
	ret nz
	ld hl,MouseY
	ld (hl),4
	inc hl
	ld (hl),92
	pop hl
	ret	
MouseHookPlayPause:
	ld hl,MouseY
	ld (hl),48
	inc hl
	ld (hl),14
	pop hl
	ret
MouseHookStop:
	ld hl,MouseY
	ld (hl),56
	inc hl
	ld (hl),30
	pop hl
	ret
MouseHookOpen:
	ld hl,MouseY
	ld (hl),56
	inc hl
	ld (hl),85
	pop hl
	ret
Quit:
	call ResetAppPage
	call CloseGUIStack
	ret
SetupGUI:
	call OpenGUIStack
	;now, set it up
	ld hl,LargeWinData
	ld de,LargeWinDataE-LargeWinData
	ld a,1
	call PushGUIStack
	ld hl,WinButtons
	ld de,WinButtonsE-WinButtons
	ld a,5
	call PushGUIStack
	ld hl,OriginalButtons
	ld de,OriginalButtonsE-OriginalButtons
	ld a,$11
	call PushGUIStack
	ld hl,Hotspot_Open
	ld de,Hotspot_OpenE-Hotspot_Open
	ld a,$0e
	call PushGUIStack
	ld hl,Hotspot_PlayPause
	ld de,Hotspot_PlayPauseE-Hotspot_PlayPause
	ld a,$0e
	call PushGUIStack
	ld hl,Hotspot_Stop
	ld de,Hotspot_StopE-Hotspot_Stop
	ld a,$0e
	call PushGUIStack
	ld hl,Hotspot_Rev
	ld de,Hotspot_RevE-Hotspot_Rev
	ld a,$0e
	call PushGUIStack
	ld hl,Hotspot_FF
	ld de,Hotspot_FFE-Hotspot_FF
	ld a,$0e
	call PushGUIStack
	ret
Button_PlayPause:
	call ResetAppPage
	ld hl,PlayPauseMask
	ld de,PlayPauseMaskE-PlayPauseMask
	ld a,$10
	call PushGUIStack
	call RenderGUI
	call playNow
	call PopGUIStack
	jp MainMouse
Button_Stop:
	call ResetAppPage
	ld a,(OpenFileFlag)
	or a
	jp z,MainMouse
	call PlayStop
	jp MainMouse
Button_FF:
	call ResetAppPage
	ld hl,SmallWinAbout
	ld de,SmallWinAboutE-SmallWinAbout
	ld a,2
	call PushGUIStack
	ld hl,SmallWinButtons
	ld de,SmallWinButtonsE-SmallWinButtons
	ld a,5
	call PushGUIStack
	ld hl,SmallWinAboutT1
	ld de,SmallWinAboutT2-SmallWinAboutT1
	ld a,4
	call PushGUIStack
	ld hl,SmallWinAboutT2
	ld de,SmallWinAboutT3-SmallWinAboutT2
	ld a,4
	call PushGUIStack
	ld hl,SmallWinAboutT3
	ld de,SmallWinAboutT4-SmallWinAboutT3
	ld a,4
	call PushGUIStack
	ld hl,SmallWinAboutT4
	ld de,SmallWinAboutT5-SmallWinAboutT4
	ld a,4
	call PushGUIStack
	ld hl,0
	call GUIMouse
DispAboutClose:
	call ResetAppPage
	ld b,6
	call PopGUIStacks

	jp MainMouse
Button_Open:
	call ResetAppPage
	ld a,0
	call FileOpen
	ld a,h
	or l
	jp z,MainMouse
	push hl
;		dec hl
;		ld a,(hl)
;		cp 4
;		jp nz,OpenFail
;		dec hl
;		ld a,(hl)
;		cp 1
;		jp nz,OpenFail
;		dec hl
;		ld a,(hl)
;		or a
;		jp nz,OpenFail
		push de
			push bc
				ld a,(OpenFileFlag)
				or a
				jr z,Button_Open2
				ld b,3
				call PopGUIStacks
Button_Open2:
				pop hl
			ld (FileSize),hl
			pop de
		pop hl
Button_Open_APIns:
	ld b,3
Button_Open_LL:
	ld de,TextLabelTemplate
	ex de,hl
	ld a,3
	sub b
	add a,a
	add a,a
	add a,a
	inc a
	ld (hl),1
	inc hl
	ld (hl),a
	inc hl
	inc hl
Button_Open_L1
	ld a,(de)
	ld (hl),a
	inc hl
	inc de
	or a
	jr nz,Button_Open_L1
	push hl
		push de
			push bc
				ld hl,TextLabelTemplate
				ld de,TextLabelTemplateE-TextLabelTemplate
				ld a,4
				call PushGUIStack
				pop bc
			pop hl
		pop de
	djnz Button_Open_LL
	ld (FilePtr),hl
	ld a,1
	ld (OpenFileFlag),a
	ld hl,0
	ld (OffsetTable),hl
	ld (OffsetSection),hl
	ld (SongNoteCurrent),hl
	push hl
	pop bc
	ld hl,(FilePtr)
CountNotes:
	push hl
	bcall(_ldhlind)
	ld a,h
	or l
	jr z,CountNotesDone
	ld de,(FilePtr)
	add hl,de
	push hl
	pop ix
CountNotesInner:
	ld a,(ix+4)
	or (ix+5)
	jr z,CountNotesNext
	inc ix
	inc ix
	inc ix
	inc ix
	inc ix
	inc ix
	inc bc
	jr CountNotesInner
CountNotesNext:
	pop hl
	inc hl
	inc hl
	jr CountNotes
CountNotesDone:
	pop hl
	push bc
	pop hl
	ld (SongNoteLength),hl
	call UpdateSlider
	jp MainMouse
OpenFail:
		pop hl
	jp MainMouse
APStart:
	push ix
	call SetupGUI
	pop hl
	push hl
	ld de,-8
	add hl,de
	bcall(_ldhlind)
	ld (FileSize),hl
	pop hl
	jp Button_Open_APIns
UpdateSlider:
	ld de,(SongNoteCurrent)
	ld a,59
	call MultADE
	ld b,h
	ld c,l
	ld de,(SongNoteLength)
	call DivABCDE
	ld a,34
	add a,c
	ld e,47
	call iGetPixel
	push af
		xor $ff
		and (hl)
		ld (hl),a
		ld b,0
		pop af
	sla a
	rl b
	or (hl)
	ld (hl),a
	dec hl
	ld a,b
	or (hl)
	ld (hl),a
	call iFastCopy
	ret
MultADE:
	ld c,0
	ld h,c
	ld l,c
	add	a,a		; optimised 1st iteration
	jr	nc,$+4
	ld	h,d
	ld	l,e
	ld b,7
MultADE1:
	add	hl,hl		; unroll 7 times
	rla			; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	adc	a,c		; ...
	djnz MultADE1
	ret
DivABCDE:
	ld hl,0
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	slia	c		; unroll 24 times
	rl	b		; ...
	rla			; ...
	adc	hl,hl		; ...
	sbc	hl,de		; ...
	jr	nc,$+4		; ...
	add	hl,de		; ...
	dec	c		; ...
	ret
playNow:
	ld hl,(FilePtr)
	ld de,(OffsetTable)
	add hl,de
	push hl
	pop ix
	ld a,(ix+0)
	or (ix+1)
	jr nz,PlaySection
playStop:
	ld hl,0						;reset stuff here
	ld (OffsetTable),hl
	ld (OffsetSection),hl
	ld (SongNoteCurrent),hl
	call UpdateSlider
	ret
playSection:
	push ix
	pop hl
	ld a,(hl)
	inc hl
	ld h,(hl)
	ld l,a
	ld de,(FilePtr)
	add hl,de
	ld de,(OffsetSection)
	add hl,de
	push hl
	pop ix
playNoteLoop:
	ld a,(ix+4)
	or (ix+5)
	jr z,playNextSection
	ld b,(ix+5)
	ld c,(ix+4)
	ld h,(ix+0)
	ld l,(ix+1)
	ld d,(ix+2)
	ld e,(ix+3)
	inc ix
	inc ix
	inc ix
	inc ix
	inc ix
	inc ix
	call playTone
	ld hl,(SongNoteCurrent)
	inc hl
	ld (SongNoteCurrent),hl
	call UpdateSlider
	ld a,KeyRow_Top
	out (1),a
	nop \ nop
	in a,(1)
	cp dkWindow
	jr z,playStop
	ld hl,(OffsetSection)
	ld de,6
	add hl,de
	ld (OffsetSection),hl
	jr playNoteLoop
playNextSection:
	ld hl,(OffsetTable)
	inc hl
	inc hl
	ld (OffsetTable),hl
	ld hl,0
	ld (OffsetSection),hl
	jp PlayNow

; Play the tone dur=bc, period = h,l,d,e (4 channel sound - h,l = left speaker, d,e = right speaker)
playTone:
	di
	xor a
	ld (toneMask1+1),a
	ld (toneMask2+1),a
	inc b 
; INIT CHANNEL A

	ld a,h
	ld (toneAPitch+1),a
	or a
	jr z,isRestA
	ld a,1
	jr notRestA
isRestA:
	xor a
notRestA:
	ld (toneAChange+1),a

; INIT CHANNEL B

	ld a,l
	ld (toneBPitch+1),a
	or a
	jr z,isRestB
	ld a,1
	jr notRestB
isRestB:
	xor a
notRestB:
	ld (toneBChange+1),a


; INIT CHANNEL C

	ld a,d
	ld (toneCPitch+1),a
	or a
	jr z,isRestC
	ld a,2
	jr notRestC
isRestC:
	xor a
notRestC:
	ld (toneCChange+1),a

; INIT CHANNEL D

	ld a,e
	ld (toneDPitch+1),a
	or a
	jr z,isRestD
	ld a,2
	jr notRestD
isRestD:
	xor a
notRestD:
	ld (toneDChange+1),a

toneMaskPreserve:
	push bc
toneMask:
	and 1
	jr z,playPart2
	ld a,(toneMask1+1)
	jr playPart1
playPart2:
	ld a,(toneMask2+1)
playPart1:
	out (bPort),a
pitchLoop:


	dec h
	jr nz,noPitchA
toneMask1:
	ld a,0
toneAChange:
	xor 0
	ld (toneMask1+1),a
toneAPitch:
	ld h,0
noPitchA:


	dec l
	jr nz,noPitchB
toneMask2:
	ld a,0
toneBChange:
	xor 0
	ld (toneMask2+1),a
toneBPitch:
	ld l,0
noPitchB:



	dec d
	jr nz,noPitchC
	ld a,(toneMask1+1)
toneCChange:
	xor 0
	ld (toneMask1+1),a
toneCPitch:
	ld d,0
noPitchC:


	dec e
	jr nz,noPitchD
	ld a,(toneMask2+1)
toneDChange:
	xor 0
	ld (toneMask2+1),a
toneDPitch:
	ld e,0
noPitchD:



extendDuration:
	ld a,0
	dec a
	ld (extendDuration+1),a
	jr nz,toneMask

	ld a,KeyRow_Top
	pop bc
	out (1),a
	in a,(1)
	cp dkY
	jr nz,notTimeToQuit
	pop hl
	ret
notTimeToQuit:
	dec c
	jp nz,toneMaskPreserve
	dec b
	jp nz,toneMaskPreserve

	ret

LargeWinData:
	.db %01111000
	.db %01001000
	.db %01011000
	.db %11011000
	.db %11000000
	.db "mobileTunes 3.1",0
LargeWinDataE:
WinButtons:
	;[which {-,[],X,00000}, onclick[-] {word}, onclick[] {word}, onclick[X] {word}]
	.db %00100000
	.dw 0,0
	.dw Quit
WinButtonsE:
Hotspot_Open:
	.db 78,43
	.db 13,10
	.dw Button_Open
Hotspot_OpenE:
Hotspot_PlayPause:
	.db 3,32
	.db 21,21
	.dw Button_PlayPause
Hotspot_PlayPauseE:
Hotspot_Stop:
	.db 26,44
	.db 9,9
	.dw Button_Stop
Hotspot_StopE:
Hotspot_Rev:
	.db 36,44
	.db 9,9
	.dw Button_Stop
Hotspot_RevE:
Hotspot_FF:
	.db 46,44
	.db 9,9
	.dw Button_FF
Hotspot_FFE:
TextLabelTemplate:
	.db 1,1
	.db 0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
	.db 0,0,0,0,0,0,0,0
TextLabelTemplateE:
OriginalButtons:
	.db -1,29
	.db 12
	.db 25
	.db $00,$1F,$C0,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$60,$30,$00
	.db $00,$00,$00,$00,$00,$00,$00,$00,$01,$80,$0C,$00,$00,$00,$00,$00
	.db $00,$00,$00,$00,$02,$1F,$C2,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.db $04,$7F,$F1,$00,$00,$00,$00,$00,$00,$00,$00,$00,$78,$F8,$F8,$FF
	.db $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FE,$01,$D1,$5C,$40,$00,$00,$00,$00
	.db $00,$00,$00,$00,$03,$EA,$3E,$40,$00,$00,$00,$00,$00,$00,$00,$00
	.db $07,$55,$57,$20,$7F,$FF,$FF,$FF,$FF,$FF,$FF,$FC,$07,$E3,$BF,$20
	.db $7F,$FF,$FF,$FF,$FF,$FF,$FF,$FC,$0F,$51,$57,$90,$7F,$FF,$FF,$FF
	.db $FF,$FF,$FF,$FC,$0F,$B0,$EF,$88,$00,$00,$00,$00,$00,$00,$00,$00
	.db $0D,$50,$57,$86,$00,$00,$00,$00,$00,$00,$00,$00,$0F,$F0,$3F,$81
	.db $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FE,$0E,$F0,$7B,$80,$00,$00,$00,$FF
	.db $FF,$FF,$00,$0E,$0F,$D0,$DF,$87,$C1,$F0,$7C,$1F,$FF,$FE,$FF,$F6
	.db $0F,$F1,$FF,$88,$22,$08,$82,$03,$FF,$FE,$C0,$F6,$07,$F3,$FF,$17
	.db $D5,$D5,$45,$00,$FF,$FE,$BF,$76,$07,$F7,$FF,$1C,$77,$9D,$F7,$00
	.db $7F,$FE,$A0,$16,$03,$FF,$FE,$1C,$77,$1D,$EF,$00,$3F,$FE,$AF,$D6
	.db $01,$FF,$FC,$1C,$77,$9D,$FF,$00,$1F,$FE,$9F,$B6,$00,$FF,$F8,$1F
	.db $F7,$DD,$EF,$00,$0F,$FE,$9F,$B6,$00,$7F,$F0,$0F,$E3,$F8,$FE,$00
	.db $07,$FE,$C0,$76,$00,$1F,$C0,$07,$C1,$F0,$7C,$00,$01,$FF,$7F,$EE
	.db $00,$00,$00,$00,$00,$00,$00,$00,$00,$3F,$FF,$FE
OriginalButtonsE:
PlayPauseMask:
	.db 10,36
	.db 12
.db $04,$82,$2C,$92,$BE,$AA,$B8,$9A,$BE,$B6,$A6,$86
PlayPauseMaskE:

SmallWinAbout:
	.db 8,8
	.db %01111000
	.db %01001000
	.db %01011000
	.db %11011000
	.db %11000000
	.db "mt3 | About",0
SmallWinAboutE:
SmallWinButtons:
	;[which {-,[],X,00000}, onclick[-] {word}, onclick[] {word}, onclick[X] {word}]
	.db %00100000
	.dw 0,0
	.dw DispAboutClose
SmallWinButtonsE:
SmallWinAboutT1:
	.db 1,1,0,"mobileTunes v3.1",0
SmallWinAboutT2:
	.db 1,8,0,"By Kerm Martian",0
SmallWinAboutT3:
	.db 1,15,0,"July 25, 2010",0
SmallWinAboutT4:
	.db 1,22,0,"www.cemetech.net",0
SmallWinAboutT5:
.end
END