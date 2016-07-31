
#define PACKET_TYPE_1 0x77

typedef struct _header {
public:
    int tag;
} common_header;

typedef struct _body_type_1 {
public:
    int id;
} body_type_1;

typedef struct _packet_type_1 {
public:
    common_header h;
    body_type_1 b;
} packet_type_1;
