#include <stdio.h>
#include <stdint.h>

typedef struct physical_layer {
    int id;
} physical_layer_t;

typedef struct datalink_layer {
    physical_layer_t physical;
    uint8_t read_buffer[32];
    uint8_t write_buffer[32];
} datalink_layer_t;

typedef struct network_layer {
    datalink_layer_t datalink;
    uint8_t endpoint_id;
} network_layer_t;

typedef struct trans_layer {
    network_layer_t network;
    uint8_t datagram[8];
    uint8_t state;
} trans_layer_t;

typedef struct sess_header {
    uint8_t handshake[32];
    uint8_t state;
} sess_header_t;

typedef struct sess_layer {
    sess_header_t hdr;
    trans_layer_t transmission;
    //queue_t rx_queue;
    //queue_t tx_queue;
    //pthread thrd;
} sess_layer_t;

typedef struct pres_layer {
    sess_layer_t session;    ///< Session layer instance
    uint32_t id;
    uint32_t status;
    float timeout;                  ///< Timeout for a roundtrip transmission
    uint32_t n_bytes_queued;     ///< Number of requests queued for transmission
}pres_layer_t;
        
typedef struct app_layer {
    pres_layer_t presentation;
    float timeout;
    uint32_t in_bytes;
    uint32_t out_bytes;

} app_layer_t;


int main()
{
}
