#ifndef _LINUX_GENERIC_H
#define _LINUX_GENERIC_H

#include <linux/types.h>

/* user mode
 */

#define PCI_TYPE0_ADDRESSES             6
#define PCI_TYPE1_ADDRESSES             2
#define PCI_TYPE2_ADDRESSES             5

#pragma pack(1)
struct PCI_COMMON_HEADER {
    __u16  VendorID;                   // (ro)
    __u16  DeviceID;                   // (ro)
    __u16  Command;                    // Device control
    __u16  Status;
    __u8   RevisionID;                 // (ro)
    __u8   ProgIf;                     // (ro)
    __u8   SubClass;                   // (ro)
    __u8   BaseClass;                  // (ro)
    __u8   CacheLineSize;              // (ro+)
    __u8   LatencyTimer;               // (ro+)
    __u8   HeaderType;                 // (ro)
    __u8   BIST;                       // Built in self test
    __u32   BaseAddresses[PCI_TYPE0_ADDRESSES];
    __u32   CIS;
    __u16   SubVendorID;
    __u16   SubSystemID;
    __u32   ROMBaseAddress;
    __u8    CapabilitiesPtr;
    __u8    Reserved1[3];
    __u32   Reserved2;
    __u8    InterruptLine;      //
    __u8    InterruptPin;       // (ro)
    __u8    MinimumGrant;       // (ro)
    __u8    MaximumLatency;     // (ro)

};

typedef struct _PCI_COMMON_CONFIG {
    struct PCI_COMMON_HEADER pci_hdr;
    __u8   DeviceSpecific[192];
} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;

enum genu_opcode {
    genu_get_pci_cfg            = 0x81,
    genu_start_wait             = 0x82,
    genu_satisfy_wait           = 0x83,
    genu_add_wait               = 0x84,
    genu_wakeup                 = 0x85,
    genu_send_signal            = 0x86,
    genu_pause_thread           = 0x87,
    genu_resume_thread          = 0x88,
};

enum genu_failure_codes {
    FSC_NOT_IDLE = 0x101,
    DEVICE_STATE_NOT_PD2,
    DEVICE_STATE_NOT_PD3,
    MEMORY_ALLOCATION_FAILURE,
    REQUEST_IRQ_FAILED,
    ILLEGAL_COMMAND,
    QUEUE_PAIR_CREATE_FAILURE_NO_PD4_ERROR,
    QUEUE_PAIR_CREATE_FAILURE_PD4_ERROR,
    QUEUE_PAIR_DELETE_FAILURE_PD4_ERROR,

};
struct genu_cmd {
    int op;
    __u64 data;
    int status;
    int debug;
    PCI_COMMON_CONFIG pci;
};

#define GENU_IOCTL_PASS_THROUGH _IOWR('P', 0x71, struct genu_cmd)

#endif /* _LINUX_GENERIC_H */
