
#define PACKET_TYPE_1 0x77

typedef struct _header {
public:
    int tag;
} header;

typedef struct _body {
public:
    int id;
} body;

typedef struct _packet {
public:
    header h;
    body b;
} packet;
