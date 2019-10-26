#include "includes\ti84pce.inc"

.assume ADL=1
.org userMem-2
.db tExtTok,tAsm84CeCmp

    call _homeup
    call _ClrScrnFull
    ld hl,TutorialText
    call _PutS
    call _GetKey
    ld h,0
    ld l,a
    call _DispHL
    call _NewLine
    call _GetKey
    call _ClrScrnFull
    res donePrgm,(iy+doneFlags)
    ret

TutorialText:
  .db "Dude, you suck! ;)",0

