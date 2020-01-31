#ifndef _RING_INC_
#define _RING_INC_

e_v buffer[SIZE_RING];
int read, write, size, data;
void rngini() {
    size = SIZE_RING;
    data = read = write = 0;
}
int rngfull() {
    if (read == (write+1)%size) return 1;
    return 0;
}
int rngempty() {
    //printf("empty = %d\n", data);
    if (data) return 0;
    return 1;
}
void rngput(e_v elem) {
    if (!rngfull()) {
        //printf("put[%d] = %d\n", write, elem);
        buffer[write] = elem;
        write = (write+1)%size;
        data++;
    }
}
e_v rngget() {
    e_v item = buffer[read];
    //printf("get[%d] = %d\n", read, item);
    read = (read+1)%size;
    data--;
    return item;
}
e_v rngpeek()
{
    return buffer[read];
}
int rngspace()
{
    return (SIZE_RING-data);
}
#endif
