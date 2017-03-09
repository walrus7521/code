#ifndef _STAK_INC_
#define _STAK_INC_

e_v buffer[SIZE_STAK];
int ptr, size;
void init_stak() {
    size = SIZE_STAK;
    ptr = 0;
}
int stkfull() {
    if (ptr == (size-1)) return 1;
    return 0;
}
int stkempty() {
    if (ptr== 0) return 1;
    return 0;
}
void stkpush(e_v elem) {
    if (!stkfull()) {
        buffer[ptr++] = elem;
    }
}
e_v stkpop() {
    e_v item = 0;
    if (!stkempty()) {
        item = buffer[--ptr];
    }
    return item;
}
e_v stkpeek()
{
    return buffer[ptr-1];
}
int stkdata()
{
    return ptr;
}
int stkspace()
{
    return (SIZE_STAK-ptr);
}

#endif
