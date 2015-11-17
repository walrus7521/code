#include <libudev.h>
#include <stdio.h>
#include <linux/types.h>

/*
 * http://stackoverflow.com/questions/25361042/how-to-list-usb-mass-storage-devices-programatically-using-libudev-in-linux
 * https://www.kernel.org/pub/linux/utils/kernel/hotplug/libudev/libudev-udev-device.html
 *
 */

static
struct udev_device*
get_child(struct udev* udev, struct udev_device* parent, const char* subsystem) {
  struct udev_device* child = NULL;
  struct udev_enumerate *enumerate = udev_enumerate_new(udev);

  udev_enumerate_add_match_parent(enumerate, parent);
  udev_enumerate_add_match_subsystem(enumerate, subsystem);
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry *entry;

  udev_list_entry_foreach(entry, devices) {
      const char *path = udev_list_entry_get_name(entry);
      child = udev_device_new_from_syspath(udev, path);
      break;
  }

  udev_enumerate_unref(enumerate);
  return child;
}

static void enumerate_usb_mass_storage(struct udev* udev) {
  struct udev_enumerate* enumerate = udev_enumerate_new(udev);
  dev_t n;

  udev_enumerate_add_match_subsystem(enumerate, "scsi");
  udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry *entry;

  udev_list_entry_foreach(entry, devices) {
      const char* path = udev_list_entry_get_name(entry);
      struct udev_device* scsi = udev_device_new_from_syspath(udev, path);

      struct udev_device* block = get_child(udev, scsi, "block");
      struct udev_device* scsi_disk = get_child(udev, scsi, "scsi_disk");

      if (block && scsi_disk) {
          printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
          printf("block = %s, %s:%s, scsi = %s\n",
                 udev_device_get_devnode(block),
                 udev_device_get_sysattr_value(scsi, "idVendor"),
                 udev_device_get_sysattr_value(block, "vendor"),
                 udev_device_get_sysattr_value(scsi, "vendor"));
          n = udev_device_get_devnum(block);
          printf("mj %d, mn %d\n", n>>8, n&0xff);
          const char *p = udev_device_get_syspath(block);
          printf("p = %s\n", p);
      }

      if (block) {
          udev_device_unref(block);
      }

      if (scsi_disk) {
          udev_device_unref(scsi_disk);
      }

      udev_device_unref(scsi);
  }

  udev_enumerate_unref(enumerate);
}

int main() {
  struct udev* udev = udev_new();

  enumerate_usb_mass_storage(udev);

  udev_unref(udev);
  return 0;
}
