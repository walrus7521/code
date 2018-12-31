#include <stdio.h>

typedef struct {
     char *buf;
     int head;
     int tail;
     int size;
} fifo_t;

void fifo_init(fifo_t * f, char * buf, int size)
{
     f->head = 0;
     f->tail = 0;
     f->size = size;
     f->buf  = buf;
}

int fifo_read(fifo_t * f, void * buf, int nbytes)
{
     int i;
     char * p;
     p = buf;
     for (i = 0; i < nbytes; i++) {
          if( f->tail != f->head ) { //see if any data is available
               *p++ = f->buf[f->tail];  //grab a byte from the buffer
               f->tail++;  //increment the tail
               if( f->tail == f->size ) {  //check for wrap-around
                    f->tail = 0;
               }
          } else {
               return i; //number of bytes read
          }
     }
     return nbytes;
}

int fifo_bytes_avail(fifo_t *f)
{
    return (f->tail - f->head);
}

int fifo_space_avail(fifo_t *f)
{
    return (f->size - (f->tail - f->head));
}

//This writes up to nbytes bytes to the FIFO
//If the head runs in to the tail, not all bytes are written
//The number of bytes written is returned
int fifo_write(fifo_t * f, const void * buf, int nbytes)
{
     int i;
     const char * p;
     p = buf;
     for(i=0; i < nbytes; i++) {
           //first check to see if there is space in the buffer
           if ((f->head + 1 == f->tail) ||
               ((f->head + 1 == f->size) && (f->tail == 0))) {
                 return i; //no more room
           } else {
               f->buf[f->head] = *p++;
               f->head++;  //increment the head
               if( f->head == f->size ) {  //check for wrap-around
                    f->head = 0;
               }
           }
     }
     return nbytes;
}
static fifo_t * uart_fifo;

void uart_fifo_init(fifo_t * fifo){
     uart_fifo = fifo;
}

void uart_isr(void)
{
    static int data = 0;
    char incoming_byte;
    incoming_byte = 'a'+data++;
    fifo_write(uart_fifo, &incoming_byte, 1); //write the data to the fifo

}

int main()
{
    int i;
    fifo_t f;
    char buffer[16];
    f.buf = buffer;
    f.size = 16;
    fifo_init(&f, buffer, 16);
    
    uart_fifo_init(&f);

    for (i = 0; i < 4; i++) {
    //while (fifo_space_avail(&f)) {
        int space = fifo_space_avail(&f);
        printf("space avail: %d\n", space);
        uart_isr();
    }

    while (fifo_bytes_avail(&f)) {
        char data;
        fifo_read(&f, &data, 1);
        printf("fifo: %x\n", data);
    }
    
}

