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
    NO_ERROR,
    OVERFLOW,
    UNDERFLOW
};
typedef uint8_t ring_status;
typedef uint8_t ret_status;

void ring_init(ring_t *ring, uint32_t size, uint8_t *buffer)
{
}

void ring_adjust(ring_t *ring, uint32_t offset)
{
}

void ring_reset(ring_t *ring)
{
}

uint8_t ring_put(ring_t *ring, uint8_t data)
{
    return 0;
}

uint8_t ring_put_data(ring_t *ring, uint32_t size, uint8_t *data)
{
    return 0;
}

uint8_t ring_get(ring_t *ring, uint8_t *data)
{
    return 0;
}

uint8_t ring_get_data(ring_t *ring, uint32_t size, uint8_t *data)
{
    return 0;
}

uint8_t ring_peek(ring_t *ring, uint8_t *data)
{
    return 0;
}

uint8_t ring_peek_at(ring_t *ring, uint32_t offset, uint8_t *data)
{
    return 0;
}

uint32_t ring_data_avail(ring_t *ring)
{
    return 0;
}

uint32_t ring_space_avail(ring_t *ring)
{
    return 0;
}

uint32_t ring_size(ring_t *ring)
{
    return 0;
}

uint32_t ring_get_error(ring_t *ring)
{
    return 0;
}

uint32_t ring_crc(ring_t *ring, uint32_t size, uint16_t *crc)
{
    return 0;
}

#endif
