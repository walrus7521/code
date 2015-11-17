/*
 * yum install libudev-devel
 *
 * pkg-config --list-all
 * pkg-config --libs libusb
 *      -lusb
 * pkg-config --libs libudev
 *      -ludev
 *
 *
 *
 * root@localhost pci]# lspci
 * 00:00.0 Host bridge: Intel Corporation 2nd Generation Core Processor Family DRAM Controller (re
 * 00:01.0 PCI bridge: Intel Corporation Xeon E3-1200/2nd Generation Core Processor Family PCI Exp
 * 00:02.0 VGA compatible controller: Intel Corporation 2nd Generation Core Processor Family Integ
 * 00:16.0 Communication controller: Intel Corporation 6 Series/C200 Series Chipset Family MEI Con
 * 00:16.3 Serial controller: Intel Corporation 6 Series/C200 Series Chipset Family KT Controller 
 * 00:19.0 Ethernet controller: Intel Corporation 82579LM Gigabit Network Connection (rev 04)
 * 00:1a.0 USB controller: Intel Corporation 6 Series/C200 Series Chipset Family USB Enhanced Host
 * 00:1b.0 Audio device: Intel Corporation 6 Series/C200 Series Chipset Family High Definition Aud
 * 00:1c.0 PCI bridge: Intel Corporation 6 Series/C200 Series Chipset Family PCI Express Root Port
 * 00:1c.2 PCI bridge: Intel Corporation 6 Series/C200 Series Chipset Family PCI Express Root Port
 * 00:1d.0 USB controller: Intel Corporation 6 Series/C200 Series Chipset Family USB Enhanced Host
 * 00:1e.0 PCI bridge: Intel Corporation 82801 PCI Bridge (rev a4)
 * 00:1f.0 ISA bridge: Intel Corporation Q67 Express Chipset Family LPC Controller (rev 04)
 * 00:1f.2 SATA controller: Intel Corporation 6 Series/C200 Series Chipset Family SATA AHCI Contro
 * 00:1f.3 SMBus: Intel Corporation 6 Series/C200 Series Chipset Family SMBus Controller (rev 04)
 * 01:00.0 SATA controller: ASMedia Technology Inc. Device 0625 (rev 01)
 * [root@localhost pci]# 
 * 
 * [root@localhost pci]# ./pciu 
 * block dev: /devices/pci0000:00/0000:00:1f.2/host0/target0:0:0/0:0:0:0/block/sda
 * block dev: /devices/pci0000:00/0000:00:1f.2/host0/target0:0:0/0:0:0:0/block/sda/sda1
 * block dev: /devices/pci0000:00/0000:00:1f.2/host0/target0:0:0/0:0:0:0/block/sda/sda2
 *      
 */

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct udev *udev;
    void *enumerate = NULL;
    struct udev_list_entry *list_entry, *list_entry2;

    udev = udev_new();
    enumerate = (void *) udev_enumerate_new(udev);

    //udev_enumerate_add_match_subsystem(enumerate, "net");
    //udev_enumerate_add_match_subsystem((struct udev_enumerate *) enumerate, "pci");
    //udev_enumerate_add_match_subsystem((struct udev_enumerate *) enumerate, "usb");
    udev_enumerate_add_match_subsystem((struct udev_enumerate *) enumerate, "block");
    //udev_enumerate_add_match_subsystem(enumerate, "tty");
    //udev_enumerate_add_match_subsystem(enumerate, "mem");
    //udev_enumerate_add_match_subsystem(enumerate, "vc");

    udev_enumerate_scan_devices((struct udev_enumerate *) enumerate);

    udev_list_entry_foreach(list_entry, udev_enumerate_get_list_entry((struct udev_enumerate *) enumerate)) {
        struct udev_device *device;
        device = udev_device_new_from_syspath(udev_enumerate_get_udev((struct udev_enumerate *) enumerate),
                                              udev_list_entry_get_name(list_entry));

        if (device == NULL)
            continue;

       udev_list_entry_foreach(list_entry2, udev_device_get_properties_list_entry(device)) {
           const char *prop, *data;
           prop = udev_list_entry_get_name(list_entry2);
           data = udev_list_entry_get_value(list_entry2);
           if (strstr(prop, "DEVPATH")) {
               if (strstr(data, "block") && strstr(data, "sd")) {
                   printf("got a block sdX device: %s\n", data);
               }
           }
           //printf("property: %s = %s\n", prop, data);
        }

        //printf("syspath %s\n", udev_device_get_syspath(device));
        //printf("sysname %s\n", udev_device_get_sysname(device));
        //printf("subsys  %s\n", udev_device_get_subsystem(device));
        //printf("devnode %s\n", udev_device_get_devnode(device));
        //printf("driver  %s\n", udev_device_get_driver(device));
        //printf("name    %s\n", udev_list_entry_get_name(list_entry));
        //printf("action  %s\n", udev_device_get_action(device));
        //printf("=================================================\n");
 
        udev_device_unref(device);
    }

    udev_enumerate_unref((struct udev_enumerate *) enumerate);
    udev_unref(udev);

    return 0;
}

