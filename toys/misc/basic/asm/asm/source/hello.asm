.nolist
#include "ti83plus.inc"
#include "dcs7.inc"
.list
.org progstart
    .db $BB,$6D
Start:
    bcall(_ClrLCDFull)
    ld a,0
    ld (curcol),a
    ld (currow),a
    ld hl,HelloWorldMessage
    bcall(_puts)
    bcall(_newline)
    ret
HelloWorldMessage:
    .db "Hello, World!",0
.end
END

