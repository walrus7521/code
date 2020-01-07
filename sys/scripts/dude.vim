" ------------------------------------------
"  Exit when your app has already been loaded
"  (or "compatible" mode set
if exists ("g:loaded_dude") || &cp
    finish
endif
let g:loaded_dude = 123 " version number
let s:keepcpo     = &cpo
set cpo&vim

command! -nargs=0 THEDUDE call s:TheDude() | delcommand THEDUDE

" Public interface
if !hasmapto('<plug>AppFunction')
    map <unique> <Leader>lz <Plug>AppFunction'
endif

" Global maps
noremap <silent> <unique> <script> <Plug>AppFunction
 \ :set lz<CR>:call <SID>TheDude2()<CR>:set nolz<CR>

" s:AppFunction: this function is available via the <Plug>/<script> interface
" above
fun! s:AppFunction()
    let str = "its the dude"
    call setline(1, str)
    call s:InternalAppFunction("42", 4)
endfun

fun! s:InternalAppFunction(str,num)
    call setline(a:num, a:str)
endfun

fun! s:TheDude()
    call setline(2, "the dudeness")
endfun

fun! s:TheDude2()
    call setline(2, "his dudifulness")
endfun

let &cpo= s:keepcpo
unlet s:keepcpo


