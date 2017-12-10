#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
 * simulate send and recv packets going through the layers
 * including authentication and threading for multiple sessions
 * use CAN as PHY
 *
 * split packets
 * route by CAN id
 *
 */

enum { RX, TX };

typedef struct can_packet {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} can_packet_t;

typedef struct physical_layer {
    uint32_t id;
    can_packet_t can;
    void *link;
} physical_layer_t;

typedef struct datalink_layer {
    uint32_t id;
    physical_layer_t physical;
    uint8_t read_buffer[32];
    uint8_t write_buffer[32];
    void *net;
} datalink_layer_t;

typedef struct network_layer {
    uint32_t id;
    datalink_layer_t datalink;
    uint8_t endpoint_id;
    void *trans;
} network_layer_t;

typedef struct trans_layer {
    uint32_t id;
    network_layer_t network;
    uint8_t datagram[8];
    uint8_t state;
    void *sess;
} trans_layer_t;

typedef struct sess_header {
    uint8_t handshake[32];
    uint8_t state;
} sess_header_t;

typedef struct sess_layer {
    uint32_t id;
    sess_header_t hdr;
    trans_layer_t transmission;
    void *pres;
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
    void *app;
}pres_layer_t;
        
typedef struct app_layer {
    uint32_t id;
    pres_layer_t presentation;
    float timeout;
    uint32_t in_bytes;
    uint32_t out_bytes;
    void *data;
} app_layer_t;

void do_phy(void *link, int dir);
void do_link(void *net, int dir);
void do_net(void *trans, int dir);
void do_trans(void *sess, int dir);
void do_sess(void *pres, int dir);
void do_pres(void *app, int dir);
void do_app(void *data, int len, int dir);
void recv(void *phy);

void show(physical_layer_t *phy)
{
    datalink_layer_t *link = phy->link;
    network_layer_t *net = link->net;
    trans_layer_t *trans = net->trans;
    sess_layer_t *sess = trans->sess;
    pres_layer_t *pres = sess->pres;
    app_layer_t *app = pres->app;
    printf("%s\n", app->data);    
}

// TX in = link
// RX in = phy
void do_phy(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            physical_layer_t *phy = in;
            printf("RX: phy->id %d\n", phy->id);
            do_link(phy->link, dir);
            break;
        }
        case TX: {
            physical_layer_t phy;
            phy.link = in;
            phy.id = 777;
            show(&phy);
            recv(&phy);
            break;
        }
    }
}

// TX in = net
// RX in = link
void do_link(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            datalink_layer_t *link = in;
            printf("RX: link->id %d\n", link->id);
            do_net(link->net, dir);
            break;
        }
        case TX: {
            datalink_layer_t link;
            link.net = in;
            link.id = 666;
            do_phy(&link, dir);
            break;
        }
    }
}

// TX in = trans
// RX in = net
void do_net(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            network_layer_t *net = in;
            printf("RX: net->id %d\n", net->id);
            do_trans(net->trans, dir);
            break;
        }
        case TX: {
            network_layer_t net;
            net.trans = in;
            net.id = 555;
            do_link(&net, dir);
            break;
        }
    }
}

// TX in = sess
// RX in = trans
void do_trans(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            trans_layer_t *trans = in;
            printf("RX: trans->id %d\n", trans->id);
            do_sess(trans->sess, dir);
            break;
        }
        case TX: {
            trans_layer_t trans;
            trans.sess = in;
            trans.id = 444;
            do_net(&trans, dir);
            break;
        }
    }
}

// TX in = pres
// RX in = sess
void do_sess(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            sess_layer_t *sess = in;
            printf("RX: sess->id %d\n", sess->id);
            do_pres(sess->pres, dir);
            break;
        }
        case TX: {
            sess_layer_t sess;
            sess.pres = in;
            sess.id = 333;
            do_trans(&sess, dir);
            break;
        }
    }
}

// TX in = app
// RX in = pres
void do_pres(void *in, int dir)
{
    switch (dir)
    {
        case RX: {
            pres_layer_t *pres = in;
            printf("RX: pres->id %d\n", pres->id);
            do_app(pres->app, 0, dir);
            break;
        }
        case TX: {
            pres_layer_t pres;
            pres.app = in;
            pres.id = 222;
            do_sess(&pres, dir);
            break;
        }
    }
}

// TX in = data
// RX in = app
void do_app(void *in, int len, int dir)
{
    switch (dir)
    {
        case RX: {
            app_layer_t *app = in;
            printf("RX: app->id %d\n", app->id);
            printf("RX: data => %s\n", app->data);
            break;
        }
        case TX: {
            app_layer_t app;
            app.id = 111;
            app.out_bytes = len;
            app.data = in;
            do_pres(&app, TX);
            break;
            }
    }
}

void route(void *pkt)
{
}

void send(void *data, int len)
{
    do_app(data, len, TX);
}

void recv(void *pkt)
{
    do_phy(pkt, RX);
}

int main()
{
    char data[] = "bart";
    send(data, 4);
}

