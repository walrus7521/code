/*
 * creates /sys/bus/root_bus
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>

#include <scsi/scsi.h>
#include <scsi/scsi_tcq.h>
#include <scsi/scsi_host.h>
#include <scsi/scsi_device.h>
#include <scsi/scsi_cmnd.h>

#include <target/target_core_base.h>
#include <target/target_core_fabric.h>
#include <target/target_core_fabric_configfs.h>

static int my_show_info(struct seq_file *m, struct Scsi_Host *host)
{
	seq_printf(m, "my_proc_info()\n");
	return 0;
}

static int my_queuecommand(struct Scsi_Host *sh, struct scsi_cmnd *sc)
{
    printk("my_queuecommand..\n");
    return 0;
}

static int my_abort_task(struct scsi_cmnd *sc)
{
    printk("my_abort_task..\n");
    return 0;
}

static int my_device_reset(struct scsi_cmnd *sc)
{
    printk("my_device_reset..\n");
    return 0;
}

static int my_target_reset(struct scsi_cmnd *sc)
{
    printk("my_target_reset..\n");
    return 0;
}

static int my_slave_alloc(struct scsi_device *sd)
{
    printk("my_slave_alloc..\n");
    return 0;
}

static struct scsi_host_template my_driver_template = {
    .show_info		            = my_show_info,
    .proc_name		            = "mybus_loopback",
    .name			            = "MyBus_Loopback",
    .queuecommand		        = my_queuecommand,
    //.change_queue_depth	        = scsi_change_queue_depth,
    .eh_abort_handler           = my_abort_task,
    .eh_device_reset_handler    = my_device_reset,
    .eh_target_reset_handler    = my_target_reset,
    .can_queue		            = 1024,
    .this_id		            = -1,
    .sg_tablesize		        = 256,
    .cmd_per_lun		        = 1024,
    .max_sectors		        = 0xFFFF,
    .use_clustering		        = DISABLE_CLUSTERING,
    .slave_alloc		        = my_slave_alloc,
    .module			            = THIS_MODULE,
    //.use_blk_tags		        = 1,
    //.track_queue_depth	        = 1,
};

struct mybus_hba {
    u8 proto_id;
    //unsigned char wwn_address[TL_WWN_ADDR_LEN];
    //struct se_hba_s *se_hba;
    //struct se_lun *tl_hba_lun;
    //struct se_port *tl_hba_lun_sep;
    struct device dev;
    struct Scsi_Host *sh;
    //struct tcm_loop_tpg tl_hba_tpgs[TL_TPGS_PER_HBA];
    //struct se_wwn tl_hba_wwn;
};

static struct device *mybus_root;
static struct mybus_hba hba;
static int mybus_host_id;

static int mybus_probe(struct device *dev)
{
    struct Scsi_Host *sh;
	int error, host_prot;

    printk("mybus_probe..\n");

    sh = scsi_host_alloc(&my_driver_template,
            sizeof(struct mybus_hba));
    if (!sh) {
        pr_err("Unable to allocate struct scsi_host\n");
        return -ENODEV;
    }
    hba.sh = sh;

    /*
     * Assign the struct mybus_hba pointer to struct Scsi_Host->hostdata
     */
    *((struct mybus_hba **)sh->hostdata) = &hba;
    /*
     * Setup single ID, Channel and LUN for now..
     */
    sh->max_id = 2;
    sh->max_lun = 0;
    sh->max_channel = 0;
    sh->max_cmd_len = SCSI_MAX_VARLEN_CDB_SIZE;

    host_prot = SHOST_DIF_TYPE1_PROTECTION | SHOST_DIF_TYPE2_PROTECTION |
                SHOST_DIF_TYPE3_PROTECTION | SHOST_DIX_TYPE1_PROTECTION |
                SHOST_DIX_TYPE2_PROTECTION | SHOST_DIX_TYPE3_PROTECTION;

    scsi_host_set_prot(sh, host_prot);
    scsi_host_set_guard(sh, SHOST_DIX_GUARD_CRC);

    error = scsi_add_host(sh, &hba.dev);
    if (error) {
        printk("%s: scsi_add_host failed\n", __func__);
        scsi_host_put(sh);
        return -ENODEV;
    }

    return 0;
}

static int mybus_remove(struct device *dev)
{
    struct Scsi_Host *sh = hba.sh;

    printk("mybus_remove..\n");
    scsi_remove_host(sh);
    scsi_host_put(sh);
    return 0;
}

static int mybus_match(struct device *dev,
				struct device_driver *dev_driver)
{
    printk("mybus_match..\n");
    return 1;
}

static struct bus_type root_bus = {
    .name			= "root_bus",
    .match			= mybus_match,
    .probe			= mybus_probe,
    .remove			= mybus_remove,
};

static struct device_driver root_driverfs = {
    .name			= "root_driver",
    .bus			= &root_bus,
};

static void mybus_release_adapter(struct device *dev)
{
    printk("mybus_release_adapter..\n");
}

static int create_hba_bus(void)
{
    int rc;
    printk("create_hba_bus..\n");
    hba.dev.bus = &root_bus;
    hba.dev.parent = mybus_root;
    hba.dev.release = &mybus_release_adapter;
    dev_set_name(&hba.dev, "mybus_adapter_%d", mybus_host_id);
    mybus_host_id++;
    rc = device_register(&hba.dev);
    if (rc) {
        printk("device_register failed for hba->dev: %d\n", rc);
        return -ENODEV;
    }
    return 0;
}

static int destroy_hba_bus(void)
{
    printk("destroy_hba_bus..\n");
    device_unregister(&hba.dev);
    return 0;
}

static int alloc_core_bus(void)
{
    int rc = -ENOMEM;

    printk("alloc_core_bus..\n");

    mybus_root = root_device_register("mybus_root_0");
    if (IS_ERR(mybus_root)) {
        printk("unable to allocate root bus\n");
        return PTR_ERR(mybus_root);
    }

    rc = bus_register(&root_bus);
    if (rc) {
        printk("bus_register failed \n");
        goto dev_unreg;
    }

    rc = driver_register(&root_driverfs);
    if (rc) {
        printk("driver_register() failed for"
                "mybus_driverfs\n");
        goto bus_unreg;
    }

    return rc;

bus_unreg:
    bus_unregister(&root_bus);
dev_unreg:
    root_device_unregister(mybus_root);
    return rc;
}

static void release_core_bus(void)
{
    printk("release_core_bus..\n");

    driver_unregister(&root_driverfs);
    bus_unregister(&root_bus);
    root_device_unregister(mybus_root);
}

static int __init mybus_init(void)
{       
    printk("mybus_init..\n");
    alloc_core_bus();
    //create_hba_bus();
    return 0;
}

static void __exit mybus_exit(void)
{       
    printk("mybus_exit..\n");
    //mybus_remove(NULL); // this is bogus
    //destroy_hba_bus();
    release_core_bus();
}

module_init(mybus_init);
module_exit(mybus_exit);
MODULE_LICENSE("GPL");

