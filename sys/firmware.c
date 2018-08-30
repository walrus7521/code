#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/firmware.h>
#include <linux/platform_device.h>

/*
 *
 * http://www.crashcourse.ca/wiki/index.php/Loading_external_firmware
 *
 */
struct platform_device *pdev;
const struct firmware *fw;

#define FIRMWARE_RT73   "rt73.bin"
MODULE_FIRMWARE(FIRMWARE_RT73);

void hexdump(const char *buffer, unsigned int length)
{
    char OffsetBuf[10];
    unsigned int LastStart = 0, i, k, j;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%03x", i);
            printk("%4s:", OffsetBuf);
        }
        if (i % 4 == 0) {
            printk(" ");
        }
        printk("%02x ", buffer[i]);
        if (i % 16 == 15 || i == length-1) {
            if (i == length-1) {
                for (k = i % 16 ; k < 15 ; k++) {
                     printk( "   " );
                     if (k % 4 == 3 && k % 16 != 0) {
                         printk(" ");
                     }
                }
            }
            printk("|");
            for (j = LastStart ; j <= i ; j++) {
                if (j % 4 == 0) {
                    printk(" ");
                }
                if (buffer[j] > 31 && buffer[j] < 127) {
                    printk("%c", buffer[j]);
                } else {
                    printk(".");
                }
            }
            if (i == length-1) {
                printk("\n");
                break;
            }
            printk("\n");
            LastStart += 16;
        }        
    }
}

static int hi(void)
{
    int err;


    pdev = platform_device_register_simple("rday", 0, NULL, 0);
    if (IS_ERR(pdev)) {
        printk(KERN_ERR "Failed to register platform device.\n");
        return -EINVAL;
    }

#if 1
    err = request_firmware(&fw, FIRMWARE_RT73, &pdev->dev);
    if (err) {
        printk(KERN_ERR "Failed to load %s, %d.\n", FIRMWARE_RT73, err);
        return -EINVAL;
    }

    printk("Downloaded firmware size: %ld.\n", fw->size);
    /* Here's where you'd load the firmware into the device. */
    hexdump(fw->data, fw->size);
    release_firmware(fw);
#endif

    printk("firmware: yo\n");
    return 0;
}

static void bye(void)
{
    printk("firmware: bye\n");
    platform_device_unregister(pdev);
}

module_init(hi);
module_exit(bye);

MODULE_AUTHOR("Robert P. J. Day, http://crashcourse.ca");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Tutorial: loading an external firmware file");
