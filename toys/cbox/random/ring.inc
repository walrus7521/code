#ifndef _RING_INC_
#define _RING_INC_

// add peek n with buffer passed in
// could be better in c++?

e_v buffer[SIZE_RING];
int read, write, size, data;
void init_ring() {
    size = SIZE_RING;
    data = read = write = 0;
}
int rngfull() {
    if (read == (write+1)%size) return 1;
    return 0;
}
int rngempty() {
    if (read == write) return 1;
    return 0;
}
void rngput(e_v elem) {
    if (!rngfull()) {
        buffer[write] = elem;
        write = (write+1)%size;
        data++;
    }
}
e_v rngget() {
    e_v item = buffer[read];
    read = (read+1)%size;
    data--;
    return item;
}
e_v rngpeek()
{
    return buffer[read];
}
int rngdata()
{
    return data;
}
int rngspace()
{
    return (SIZE_RING-data);
}
#endif
