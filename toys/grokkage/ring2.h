#ifndef __ring2_h_
#define __ring2_h_

#include <stdint.h>

typedef struct {
    uint32_t head;
    uint32_t tail;
    uint32_t data_avail;
    uint32_t size;
    uint32_t status;
    uint8_t *buffer;
} ring_t;

enum {
    /* return status */
    SUCCESS,
    FAIL,
    /* ring status */
    NO_ERROR  = 0,
    UNDERFLOW = 0x40,
    OVERFLOW = 0x80
};

typedef uint8_t ring_status;
typedef uint8_t ret_status;
void ring_reset(ring_t *ring);

#define RING_GETINDEX(offset, ring) (((ring)->tail+offset)%(ring)->size) 
#define RING_INCTAIL_RAW(ring)              (ring)->tail++; \
                                            if( (ring)->tail == (ring)->size ) \
                                            { \
                                                (ring)->tail = 0; \
                                            } \
                                            (ring)->data_avail--;
#define RING_INCHEAD_RAW(ring)              (ring)->head++; \
                                            if( (ring)->head == (ring)->size ) \
                                            { \
                                                (ring)->head = 0; \
                                            } \
                                            (ring)->data_avail++;

void ring_init(ring_t *ring, uint32_t size, uint8_t *buffer)
{
    ring->buffer = buffer;
    ring->size = size;
    ring->head = ring->tail = 0;
    ring->status = NO_ERROR;
    ring->data_avail = 0;
}

void ring_adjust(ring_t *ring, uint32_t offset)
{
    ring->tail = RING_GETINDEX(offset, ring);    
    if(offset <= ring->data_avail) {
        ring->data_avail -= offset;
    } else {
        ring_reset(ring);
    }
}

void ring_reset(ring_t *ring)
{
    ring->head = 0;
    ring->tail = 0;
    ring->data_avail = 0;
    ring->status = NO_ERROR;
}

uint8_t ring_put(ring_t *ring, uint8_t data_in)
{
    uint8_t ret = SUCCESS;
    if (ring->data_avail == ring->size) {
        // The buffer is full, so move the tail forward - data has now been lost
        RING_INCTAIL_RAW(ring); // Move the tail
        ring->status |= OVERFLOW;
        ret = FAIL;
    }
    ring->buffer[ring->head] = data_in;
    RING_INCHEAD_RAW(ring); // Move the head to next entry
    return ret;
}

uint8_t ring_put_data(ring_t *ring, uint32_t size, uint8_t *data)
{
    return 0;
}

uint8_t ring_get(ring_t *ring, uint8_t *data_out)
{
    uint8_t ret = FAIL;
    if (ring->data_avail) {
        *data_out = ring->buffer[ring->tail];
        RING_INCTAIL_RAW(ring);
        ret = SUCCESS;
    }
    return ret;
}

uint8_t ring_get_data(ring_t *ring, uint32_t size, uint8_t *data)
{
    return 0;
}

uint8_t ring_peek(ring_t *ring, uint8_t *data)
{
    return 0;
}

uint8_t ring_peek_at(ring_t *ring, uint32_t offset, uint8_t *data_out)
{
    uint8_t ret = SUCCESS;
    *data_out = ring->buffer[RING_GETINDEX(offset, ring)];
    if(offset >= ring->data_avail) { // offset is 0-based, data_avail is 1-based, so offset must be less than data_avail
        ret = FAIL;
    }
    return ret;
}

uint32_t ring_data_avail(ring_t *ring)
{
    return ring->data_avail;
}

uint32_t ring_space_avail(ring_t *ring)
{
    return (ring->size - ring->data_avail);
}

uint32_t ring_size(ring_t *ring)
{
    return ring->size;
}

uint32_t ring_get_error(ring_t *ring)
{
    return ring->status;
}

uint32_t ring_crc(ring_t *ring, uint32_t size, uint16_t *crc)
{
    return 0xdeadbeef;
}

#endif
