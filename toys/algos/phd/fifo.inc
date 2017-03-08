#ifndef _FIFO_INC_
#define _FIFO_INC_

int fifo_id;    // int fifo passed in
int head;       // head index of the FIFO
int tail;       // tail index of the FIFO
int data_avail; // number of data available in the FIFO
int fifo_size;       // size of the FIFO
int status;     // status of the FIFO
char *buffer; // pointer to FIFO buffer

void fifo_init(int fifo, char *in_buf, int size)
{
    fifo_id = fifo;
    fifo_size = size;
    buffer = in_buf;
}
void fifo_reset(int fifo)
{
    head = 0;
    tail = 0;
    data_avail = 0;
}
int fifo_enqueue(int fifo, char in_data)
{
    if (data_avail == fifo_size) {
        return -1;
    }
    buffer[head] = in_data;
    head++;
    if (head == fifo_size) {
        head = 0;
    }
    data_avail++;
    return 0;
}
int fifo_dequeue(int fifo, char *out_data)
{
    if (data_avail) {
        *out_data = buffer[tail];
        tail++;
        if (tail == fifo_size) {
            tail = 0;
        }
        data_avail--;
    }
    return 0;
}
int fifo_peek_relative(int fifo, int offset, char *out_data)
{
    int status = 0;
    *out_data = buffer[(tail+offset)%fifo_size];
    if (offset >= data_avail) {
        status = -1;
    }
    return status;
}
void fifo_adjust(int fifo, int offset)
{
    tail = (tail+offset)%fifo_size;
    if (offset <= data_avail) {
        data_avail -= offset;
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
    if (data_size > data_avail) {
        data_size = data_avail;
    }
    if (tail + data_size <= fifo_size) {
        *crc = calc_crc16(&buffer[tail], data_size);
    } else { // packet wraps
        *crc = calc_crc16(&buffer[tail], fifo_size - tail);
        *crc = calc_continue_crc16(buffer, data_size - (fifo_size - tail), crc);
    }
    return data_size;
}
int fifo_peek_data(int fifo, void * dest, int data_size)
{
    if (data_avail < data_size)
    {
        data_size = data_avail;
    }
    if((tail + data_size) <= fifo_size) { // packet doesn't wrap
        memcpy((char *) dest, &buffer[tail], data_size);
    } else { // Packet wraps... will take two memcpys
        memcpy((char *) dest, &buffer[tail], fifo_size - tail);
        memcpy((char *) dest + (fifo_size - tail), buffer, data_size - (fifo_size - tail));
    }
    return data_size;
}
int fifo_enqueue_data(int fifo, void * src, int data_size)
{
    if (fifo_size < (data_size + data_avail)) {
        data_size = fifo_size - data_avail;
    }

    if ((head + data_size) <= fifo_size) { // no wrap
        memcpy(&buffer[head], (char *) src, data_size);
    } else { // wraps... 2 copy's
        memcpy(&buffer[head], src, fifo_size - head);
        memcpy(buffer, (char *) src + (fifo_size - head), data_size - (fifo_size - head));
    }
    data_avail += data_size;
    head = (head + data_size) % fifo_size;

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
    status = 0;
}
int  fifo_get_num_data_avail(int fifo)
{
    return data_avail;
}
int  fifo_get_space_avail(int fifo)
{
    return (fifo_size - data_avail);
}
int  fifo_get_error_status(int fifo)
{
    return status;
}
int  fifo_get_size(int fifo)
{
    return fifo_size;
}
char fifo_peek(int fifo)
{
    return buffer[tail];
}

#endif
