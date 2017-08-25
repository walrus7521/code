typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned int __u32;
typedef unsigned long long __u64;

typedef struct {
    __u8 element_type;
} ELEMENT_HEADER;

typedef struct {
    __u8 mode;
} TRANSPORT;

typedef struct {
    __u8 scenario_type;
    __u8 scenario_number;
    __u32 timeout;
    __u32 location_of_next_step;
} SCENARIO;

typedef struct {
    ELEMENT_HEADER elementheader;
    __u32 command_offset;
    __u8 data_transfer_direction;
    __u16 queue_number;
    __u8 ring_immediately;
} SEND;

typedef struct {
    ELEMENT_HEADER elementheader;
    __u16 scenario_number;
} ACTIVATE;

typedef struct {
    ELEMENT_HEADER elementheader;
    __u8 record_a_pass_or_fail;
    __u8 continue_or_stop_test;
    __u32 location_of_message_to_log;
    __u32 location_of_object_to_log;
} LOG;

typedef struct {
    ELEMENT_HEADER elementheader;
    __u16 signal_number;
    __u32 timeout;
} WAIT;
