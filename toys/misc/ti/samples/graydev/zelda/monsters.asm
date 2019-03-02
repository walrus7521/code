;================================================
; monster data
;================================================

monsterSpriteCombinationsLookup:
	.dw pig

pig:
	.db 4,5,6,7 ;up1
	.db 9+128,8+125,11+128,10+128
	.db 0,1,2,3
	.db 8,9,10,11

	.db 5+128,4+128,7+128,6+128 ;up2
	.db 12+128,13+128,15+128,14+128
	.db 1+128,0+128,3+128,2+128
	.db 12,13,14,15


;================================================
; monster database
;================================================
; all the monster info

	;ai_type, draw_type, hp_start, speed, future, future
monsterDatabase:
	.db 0,0,10,1,0,0	;pig

;================================================
; monster sprites
;================================================
monsterSpritesDatabase:
	.dw monsterSprites+0	;pig


monsterSprites:
#include monsters.spr
