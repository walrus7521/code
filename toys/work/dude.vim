" ------------------------------------------
"  Exit when your app has already been loaded
"  (or "compatible" mode set
if exists ("g:loaded_dude") || &cp
    finish
endif
let g:loaded_dude = 123 " version number
let s:keepcpo     = &cpo
set cpo&vim

" Public interface
if !hasmapto('<plug>AppFunction')
    map <unique> <Leader>lz <Plug>AppFunction'
endif

" Global maps
noremap <silent> <unique> <script> <Plug>AppFunction
 \ :set lz<CR>:call <SID>AppFunction()<CR>:set nolz<CR>

" s:AppFunction: this function is available via the <Plug>/<script> interface
" above
fun! s:AppFunction()
    let str = "its the dude"
    call setline(1, str)
    call s:InternalAppFunction()
endfun

fun! s:InternalAppFunction(...)
    let str = "dudette"
    call setline(2, str)
endfun

let &cpo= s:keepcpo
unlet s:keepcpo


