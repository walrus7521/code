;--------------------------------------------------------------------------------------------------
;			Document DE 7
;			by Kerm Martian, christopher@cemetech.net
;			May 20, 2010
;--------------------------------------------------------------------------------------------------
; Notes:
;    Oldsize contains a size only if there is an open file that is already saved.  Otherwise 0
;    SavedFilePtr contains a location if there is an already-saved file open. Otherwise 0
;    OpenFileFlag contains 0 for NO edit context, 1 for an edit context.  If this is 1 and
;		(SavedFilePtr) is 0, then the saveas routine needs to be invoked.
;--------------------------------------------------------------------------------------------------

.nolist
#define TASM
#include "ti83plus.inc"
#include "dcs7.inc"
OpenFileFlag	.equ AppBackupScreen+94		;byte
SavedFilePtr	.equ AppBackupScreen+95		;word
OldSize			.equ AppBackupScreen+97		;word


.list
	.org progstart
#IFDEF TI83P
	.db $BB,$6D
#ENDIF
INIT:
	xor d
#IFDEF TI83P
	.db $C9
#ENDIF
	jr Start
	.dw $0000
	.db $07,$00
	.dw Icon
	.dw $0000
	.dw Apstart			;the routine to open files.  DCS will start you here instead of at $9D95
						;if a file is pending
	.db $31,$7F			;argh, this be an APMain
	.db $02				;number of accepted filetypes
MyType1:
	.db 0,1,1			;plaintext
MyType2:
	.db 0,1,2			;DDE6 text
Icon:				;a 16x16 icon
	.db %11111111,%11111000
	.db %10000000,%00001100
	.db %10111100,%00001010
	.db %10010010,%00001111
	.db %10010010,%01010001
	.db %10010010,%10101001
	.db %10111100,%01010101
	.db %10000000,%00000001
	.db %10101010,%10101001
	.db %10010101,%01010101
	.db %10101010,%10101001
	.db %10000000,%00000001
	.db %10010101,%01010101
	.db %10101010,%10101001
	.db %10000000,%00000001
	.db %11111111,%11111111
IconAP:				;a 16x16 icon
	.db $3F,$F0,$20,$18
	.db $E0,$14,$A0,$1E
	.db $A0,$02,$AF,$C2
	.db $A6,$62,$A6,$32
	.db $A6,$32,$A6,$32
	.db $A6,$62,$AF,$C2
	.db $A0,$02,$BF,$FE
	.db $80,$08,$FF,$F8
START:                          	;main routines
	;first, set up pointers
	xor a
	ld h,a
	ld l,a
	ld (OpenFileFlag),a
	ld (SavedFilePtr),hl
	ld (OldSize),hl
RenderMain:
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
	ld hl,TaskbarIcons
	ld de,TaskbarIconsE-TaskbarIcons
	ld a,$11
	call PushGUIStack
	ld hl,HotspotNew
	ld de,6
	ld a,$0E
	call PushGUIStack
	ld hl,HotspotOpen
	ld de,6
	ld a,$0E
	call PushGUIStack
	ld hl,HotspotSaveAs
	ld de,6
	ld a,$0E
	call PushGUIStack
	ld hl,HotspotAbout
	ld de,6
	ld a,$0E
	call PushGUIStack
RenderLoop:
	ld a,(OpenFileFlag)
	or a
	jr nz,DispTextbox
	ld hl,NullBox
	ld de,NullBoxE-NullBox
	ld a,$16
	call PushGUIStack
	jr RenderMain2
DispTextbox:
	ld hl,(SavedFilePtr)
	ld a,h
	or l
	jr nz,DispTextboxContents
	ld hl,Textboxheader
	ld de,TextboxheaderE-Textboxheader
	ld a,$0f
	call PushGUIStack
	jr RenderMain2
DispTextboxContents:
	ld hl,(OldSize)
	ld de,TextboxHeaderE-TextboxHeader
	add hl,de
	ld de,-8
	add hl,de
	ld de,TextboxHeader
	ld a,$0f
	ex de,hl
	call PushGUIStack
	call GetTextboxData
	push hl
	ld de,(SavedFilePtr)
	ld hl,8
	add hl,de
	pop de
	;ex de,hl
	ldir					;bc set by GetTextboxData
RenderMain2:
	ld hl,0
	call GUIMouse
DocDEClose:
	call ResetAppPage
	call CheckSaveInvocation
	call CloseGUIStack
	ret
Apstart:										;set up ap pointers now
	push ix
		pop hl
	ld de,-8
	add hl,de
	ld (SavedFilePtr),hl
	dec hl
	dec hl
	bcall(_ldhlind)
	ld (OldSize),hl
	ld a,1
	ld (OpenFileFlag),a
	jp RenderMain
NewFile:
	call ResetAppPage
	call CheckSaveInvocation
	ld a,1
	ld (OpenFileFlag),a
	ld hl,0
	ld (SavedFilePtr),hl
	ld (OldSize),hl
	call CloseGUIStack
	jp RenderMain
OpenFile:
	call ResetAppPage
	call CheckSaveInvocation
	xor a							;Only show files for DocDE
	call FileOpen
	ld a,h
	or l
	jp z,RenderMain
	push de
		ld de,-8
		add hl,de
		ld (SavedFilePtr),hl
		pop hl
	bcall(_ldhlind)
	ld (OldSize),hl
	ld a,1
	ld (OpenFileFlag),a
	jp RenderMain
SaveFileAs:
	call ResetAppPage
	ld a,(OpenFileFlag)
	or a
	jp z,RenderMain
	ld hl,(SavedFilePtr)
	ld a,h
	or l
	call nz,CheckSaveInvocation
	;*** do setup
	call getTextboxData			;sets hl and bc
	ld de,MyType2
	xor a
	call FileSaveAs
	ld a,h
	or l
	jp z,RenderMain
	push de
		inc de
		inc de
		ld (SavedFilePtr),de
		pop hl
	bcall(_ldhlind)
	ld (OldSize),hl
	ld a,1
	ld (OpenFileFlag),a
	;*** MUST CloseGUIStack and update ptrs from result
	call CloseGUIStack
	jp RenderMain
CheckSaveInvocation:
	ld a,(OpenFileFlag)
	or a
	ret z
	ld hl,(SavedFilePtr)
	ld a,h
	or l
	jr nz,CheckSaveUpdate

	call GetTextboxData
	ld de,MyType2
	xor a
	call FileSaveAs

	ld a,h
	or l
	jr nz,CheckSaveInvocation_Saved
	xor a
	ld (OpenFileFlag),a
	ret
CheckSaveInvocation_Saved:
	push de
		inc de
		inc de
		ld (SavedFilePtr),de
		pop hl
	bcall(_ldhlind)
	ld (OldSize),hl
	ld a,1
	ld (OpenFileFlag),a
	ret
CheckSaveUpdate:
	;*** update existing pointers and data
	ld hl,(SavedFilePtr)
	ld de,8
	add hl,de
	push hl
		ld hl,-8
		ld de,(OldSize)
		add hl,de
		pop de
	push de
		ex de,hl
		bcall(_deletemem)
		;ld hl,8
		;ld (SavedFilePtr),hl
		;*** update size bytes
		call GetTextboxData
		push bc
			pop hl
		ld de,8
		add hl,de
		ld (OldSize),hl
		push bc
			pop hl
		pop de
	push de
		bcall(_insertmem)
		ld hl,(SavedFilePtr)
		dec hl
		dec hl
		ld de,(OldSize)
		ld (hl),e
		inc hl
		ld (hl),d
		;*** insert required # of byte
		call GetTextboxData
		pop de
	ldir
	;*** now copy those bytes
	;*** update size bytes
	;second, add bc bytes at hl
	ret
GetTextboxData:
	call GUIFindFirst
	ld b,6
CheckSaveUpdateLoop:

	push bc
		call GUIFindNext
		pop bc
	djnz CheckSaveUpdateLoop
	push hl
		bcall(_ldhlind)
		ld de,-9					;7+size word+type byte
		add hl,de
		pop de
	ex de,hl
	push de
		ld de,9
		add hl,de
		pop bc
	; hl = data location
	; bc = data size
	ret
DispAbout:
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
	jp RenderMain2
LargeWinData:
	.db %11100000
	.db %10110000
	.db %10010000
	.db %10010000
	.db %11110000
	.db "Document DE 7",0
LargeWinDataE:
WinButtons:
	;[which {-,[],X,00000}, onclick[-] {word}, onclick[] {word}, onclick[X] {word}]
	.db %00100000
	.dw 0,0
	.dw DocDEClose
WinButtonsE:
HotspotNew:
	.db 0,0,7,7
	.dw NewFile
HotspotOpen:
	.db 8,0,11,7
	.dw OpenFile
HotspotSaveAs:
	.db 19,0,9,7
	.dw SaveFileAs
HotspotAbout:
	.db 28,0,9,7
	.dw DispAbout
TaskbarIcons:
	.db 0,0,5,8
	.db %00000001,%00000000,%00100000,%00010000,%00001000
	.db %01111001,%00110000,%00100111,%11010011,%11001000
	.db %01001101,%01001111,%10101100,%11010110,%01101000
	.db %01000101,%01000000,%10101111,%11010000,%11001000
	.db %01000101,%01000000,%10101000,%01010001,%10001000
	.db %01000101,%01000000,%10101000,%01010000,%00001000
	.db %01111101,%01111111,%10101111,%11010001,%10001000
	.db %00000001,%00000000,%00100000,%00010000,%00001000
TaskbarIconsE:
NullBox:
	.db 0,9,94,45,%10101010
NullBoxE:
TextBoxHeader:
	.db -1,8,7,95,0,0,0
TextBoxHeaderE:

SmallWinAbout:
	.db 8,8
	.db %11100000
	.db %10110000
	.db %10010000
	.db %10010000
	.db %11110000
	.db "DocDE7 | About",0
SmallWinAboutE:
SmallWinButtons:
	;[which {-,[],X,00000}, onclick[-] {word}, onclick[] {word}, onclick[X] {word}]
	.db %00100000
	.dw 0,0
	.dw DispAboutClose
SmallWinButtonsE:
SmallWinAboutT1:
	.db 1,1,0,"Document DE v7.0",0
SmallWinAboutT2:
	.db 1,8,0,"By Kerm Martian",0
SmallWinAboutT3:
	.db 1,15,0,"July 25, 2010",0
SmallWinAboutT4:
	.db 1,22,0,"www.cemetech.net",0
SmallWinAboutT5:
.end
END