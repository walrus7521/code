#ifndef _RING_INC_
#define _RING_INC_

e_v buffer[SIZE_RING];
int read, write, size;
void init_ring() {
    size = SIZE_RING;
    read = write = 0;
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
    }
}
e_v rngget() {
    e_v item = buffer[read];
    read = (read+1)%size;
    return item;
}

#endif
