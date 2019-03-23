section .data               ; section decl

msg:     db  "Hello, world!", 10 ; the string
.len:    equ $ - msg

global start               ; default entry point for ELF linking

section .text               ; section decl


start:

; write() call
    push dword msg.len
    push dword msg
    push dword 1

    mov eax, 4
    sub esp, 4
    int 0x80
    add esp, 16

; exit() call
    push dword 0
    mov eax, 1
    sub esp, 12
    int 0x80


