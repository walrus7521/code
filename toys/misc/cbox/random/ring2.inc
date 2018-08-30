#ifndef _FIFO_INC_
#define _FIFO_INC_

#define MAX_FIFOS 32

typedef struct fifo {
    int fifo_id;    // int fifo passed in
    int head;       // head index of the FIFO
    int tail;       // tail index of the FIFO
    int data_avail; // number of data available in the FIFO
    int fifo_size;       // size of the FIFO
    int status;     // status of the FIFO
    char *buffer; // pointer to FIFO buffer
} fifo;

fifo fifos[MAX_FIFOS];

void fifo_init(int fifo, char *in_buf, int size)
{
    fifos[fifo].fifo_id = fifo;
    fifos[fifo].fifo_size = size;
    fifos[fifo].buffer = in_buf;
}
void fifo_reset(int fifo)
{
    fifos[fifo].head = 0;
    fifos[fifo].tail = 0;
    fifos[fifo].data_avail = 0;
}
int fifo_enqueue(int fifo, char in_data)
{
    if (fifos[fifo].data_avail == fifos[fifo].fifo_size) {
        return -1;
    }
    fifos[fifo].buffer[fifos[fifo].head] = in_data;
    fifos[fifo].head++;
    if (fifos[fifo].head == fifos[fifo].fifo_size) {
        fifos[fifo].head = 0;
    }
    fifos[fifo].data_avail++;
    return 0;
}
int fifo_dequeue(int fifo, char *out_data)
{
    if (fifos[fifo].data_avail) {
        *out_data = fifos[fifo].buffer[fifos[fifo].tail];
        fifos[fifo].tail++;
        if (fifos[fifo].tail == fifos[fifo].fifo_size) {
            fifos[fifo].tail = 0;
        }
        fifos[fifo].data_avail--;
    }
    return 0;
}
int fifo_peek_relative(int fifo, int offset, char *out_data)
{
    fifos[fifo].status = 0;
    *out_data = fifos[fifo].buffer[(fifos[fifo].tail+offset)%fifos[fifo].fifo_size];
    if (offset >= fifos[fifo].data_avail) {
        fifos[fifo].status = -1;
    }
    return fifos[fifo].status;
}
void fifo_adjust(int fifo, int offset)
{
    fifos[fifo].tail = (fifos[fifo].tail+offset)%fifos[fifo].fifo_size;
    if (offset <= fifos[fifo].data_avail) {
        fifos[fifo].data_avail -= offset;
    } else {
        fifo_reset(fifo);
    }
}

short calc_crc16(char *buffer, int size)
{
    return 0xdead;
}
short calc_continue_crc16(char *buffer, int size, short *crc)
{
    return *crc + 0xbeef;
}

int fifo_calc_crc16(int fifo, int data_size, short *crc)
{
    if (data_size > fifos[fifo].data_avail) {
        data_size = fifos[fifo].data_avail;
    }
    if (fifos[fifo].tail + data_size <= fifos[fifo].fifo_size) { // no wrap
        *crc = calc_crc16(&fifos[fifo].buffer[fifos[fifo].tail], data_size);
    } else { // wrap
        *crc = calc_crc16(&fifos[fifo].buffer[fifos[fifo].tail], fifos[fifo].fifo_size - fifos[fifo].tail);
        *crc = calc_continue_crc16(fifos[fifo].buffer, data_size - (fifos[fifo].fifo_size - fifos[fifo].tail), crc);
    }
    return data_size;
}
int fifo_peek_data(int fifo, void * dest, int data_size)
{
    if (fifos[fifo].data_avail < data_size)
    {
        data_size = fifos[fifo].data_avail;
    }
    if((fifos[fifo].tail + data_size) <= fifos[fifo].fifo_size) { // no wrap
        memcpy((char *) dest, &fifos[fifo].buffer[fifos[fifo].tail], data_size);
    } else { // wrap
        memcpy((char *) dest, &fifos[fifo].buffer[fifos[fifo].tail], fifos[fifo].fifo_size - fifos[fifo].tail);
        memcpy((char *) dest + (fifos[fifo].fifo_size - fifos[fifo].tail), fifos[fifo].buffer, data_size - (fifos[fifo].fifo_size - fifos[fifo].tail));
    }
    return data_size;
}
int fifo_enqueue_data(int fifo, void * src, int data_size)
{
    if (fifos[fifo].fifo_size < (data_size + fifos[fifo].data_avail)) {
        data_size = fifos[fifo].fifo_size - fifos[fifo].data_avail;
    }

    if ((fifos[fifo].head + data_size) <= fifos[fifo].fifo_size) { // no wrap
        memcpy(&fifos[fifo].buffer[fifos[fifo].head], (char *) src, data_size);
    } else { // wrap
        memcpy(&fifos[fifo].buffer[fifos[fifo].head], src, fifos[fifo].fifo_size - fifos[fifo].head);
        memcpy(fifos[fifo].buffer, (char *) src + (fifos[fifo].fifo_size - fifos[fifo].head), data_size - (fifos[fifo].fifo_size - fifos[fifo].head));
    }
    fifos[fifo].data_avail += data_size;
    fifos[fifo].head = (fifos[fifo].head + data_size) % fifos[fifo].fifo_size;

    return data_size;
}
int fifo_dequeue_data(int fifo, void * dest, int data_size)
{
    int bytes_read = 0;
    bytes_read = fifo_peek_data(fifo, dest, data_size);
    fifo_adjust(fifo, bytes_read);
    return bytes_read;
}

void fifo_clear_errors(int fifo)
{
    fifos[fifo].status = 0;
}
int  fifo_get_num_data_avail(int fifo)
{
    return fifos[fifo].data_avail;
}
int  fifo_get_space_avail(int fifo)
{
    return (fifos[fifo].fifo_size - fifos[fifo].data_avail);
}
int  fifo_get_error_status(int fifo)
{
    return fifos[fifo].status;
}
int  fifo_get_size(int fifo)
{
    return fifos[fifo].fifo_size;
}
char fifo_peek(int fifo)
{
    return fifos[fifo].buffer[fifos[fifo].tail];
}

#endif
