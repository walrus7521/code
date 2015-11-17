#include <usb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct usb_dev_handle *hdev;
    struct usb_bus *bus;
    struct usb_device *dev;
    //unsigned char buffer[64];
    //int rc;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (bus = usb_busses; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            printf("Bus %03x Device %03x: ID %04x:%04x\n", 
                    bus->location, dev->devnum, dev->descriptor.idVendor, dev->descriptor.idProduct);
#if 0
            printf("dev class    %x\n", dev->descriptor.bDeviceClass);
            printf("dev subclass %x\n", dev->descriptor.bDeviceSubClass);
            printf("dev protocol %x\n", dev->descriptor.bDeviceProtocol);
            printf("vendor id    %x\n", dev->descriptor.idVendor);
            printf("product id   %x\n", dev->descriptor.idProduct);
            printf("dev num      %x\n", dev->devnum);
            printf("name         %s\n", dev->filename);
            printf("num children %d\n", dev->num_children);
            printf("======================================\n");
#endif
#if 0
            switch (dev->descriptor.bDeviceClass) {
                case USB_CLASS_PER_INTERFACE: {
                    int i;
                    for (i = 0; i < dev->config->bNumInterfaces; i++) {
                        int j;
                        struct usb_interface *usb_if = &dev->config->interface[i];
                        for (j = 0; j < usb_if->num_altsetting; j++) {
                            struct usb_interface_descriptor *usb_id = &usb_if->altsetting[j];
                            switch (usb_id->bInterfaceClass) {
                                case USB_CLASS_AUDIO:
                                    printf("audio\n");
                                    break;
                                case USB_CLASS_COMM:
                                    printf("comm\n");
                                    break;
                                case USB_CLASS_HID:
                                    printf("hid\n");
                                    break;
                                case USB_CLASS_PRINTER:
                                    printf("printer\n");
                                    break;
                                case USB_CLASS_PTP:
                                    printf("ptp\n");
                                    break;
                                case USB_CLASS_MASS_STORAGE:
                                    printf("mass storage\n");
                                    break;
                                case USB_CLASS_HUB:
                                    printf("hub\n");
                                    break;
                                case USB_CLASS_DATA:
                                    printf("data\n");
                                    break;
                                case USB_CLASS_VENDOR_SPEC:
                                    printf("vendor specific\n");
                                    break;
                            }
                            int k;
                            struct usb_endpoint_descriptor *usb_ed;
                            for (k = 0; k < usb_id->bNumEndpoints; k++) {
                                usb_ed = &usb_id->endpoint[k];
                                switch (usb_ed->bDescriptorType) {
                                    case USB_DT_DEVICE:
                                        printf("  ..DEVICE\n");
                                        break;
                                    case USB_DT_CONFIG:
                                        printf("  ..CONFIG\n");
                                        break;
                                    case USB_DT_STRING:
                                        printf("  ..STRING\n");
                                        break;
                                    case USB_DT_INTERFACE:
                                        printf("  ..INTERFACE\n");
                                        break;
                                    case USB_DT_ENDPOINT:
                                        printf("  ..ENDPOINT\n");
                                        break;
                                    case USB_DT_HID:
                                        printf("  ..HID\n");
                                        break;
                                    case USB_DT_REPORT:
                                        printf("  ..REPORT\n");
                                        break;
                                    case USB_DT_PHYSICAL:
                                        printf("  ..PHYSICAL\n");
                                        break;
                                    case USB_DT_HUB:
                                        printf("  ..HUB\n");
                                        break;
                                }
                                usb_ed->bmAttributes &= USB_ENDPOINT_TYPE_MASK;
                                if (usb_ed->bmAttributes & USB_ENDPOINT_TYPE_CONTROL) {
                                    printf("       .. CONTROL\n");
                                }
                                if (usb_ed->bmAttributes & USB_ENDPOINT_TYPE_ISOCHRONOUS) {
                                    printf("       .. ISOCHRONOUS\n");
                                }
                                if (usb_ed->bmAttributes & USB_ENDPOINT_TYPE_BULK) {
                                    printf("       .. BULK\n");
                                }
                                if (usb_ed->bmAttributes & USB_ENDPOINT_TYPE_INTERRUPT) {
                                    printf("       .. INTERRUPT\n");
                                }
                            }
                        }
                    }
                    break;
                }
                case USB_CLASS_AUDIO:
                    printf("audio\n");
                    break;
                case USB_CLASS_COMM:
                    printf("comm\n");
                    break;
                case USB_CLASS_HID:
                    printf("hid\n");
                    break;
                case USB_CLASS_PRINTER:
                    printf("printer\n");
                    break;
                case USB_CLASS_PTP:
                    printf("ptp\n");
                    break;
                case USB_CLASS_MASS_STORAGE:
                    printf("mass storage\n");
                    break;
                case USB_CLASS_HUB:
                    printf("hub\n");
                    break;
                case USB_CLASS_DATA:
                    printf("data\n");
                    break;
                case USB_CLASS_VENDOR_SPEC:
                    printf("vendor specific\n");
                    break;

            }
#endif
            hdev = NULL;
            hdev = usb_open(dev);
            if (hdev) {
                //memset(buffer, 0, 64);
                /*
                 *  usb_control_msg(usb_dev_handle *dev,
                 *                  int request_type,
                 *                  int request,
                 *                  int value,
                 *                  int index,
                 *                  char *bytes,
                 *                  int size,
                 *                  int timeout);
                 */
                //rc = usb_control_msg(hdev, 0x21, 9, 0x2, 0x0, (char*)buffer, 64, 100);
                //printf("usb result %d\n", rc);
                usb_close(hdev);
            }
        }
    }

    return 0;
}

