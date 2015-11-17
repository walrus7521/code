#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int event_ids = 0;

struct nvme_data {
    struct list_head list;
    char info[64];
};

static LIST_HEAD(nvme_event_list);

static void dummy(void)
{
    int i;
    struct nvme_data *data;

    for (i = 0; i < 16; i++, event_ids++) {
        data = kmalloc(sizeof(struct nvme_data), GFP_KERNEL);
        if (data) {
            sprintf(data->info, "Queue no: %d => %d entries\n", i, event_ids);
            list_add_tail(&data->list, &nvme_event_list);
        }
    }
}

static void *nvme_seq_start(struct seq_file *seq, loff_t *pos)
{
    struct nvme_data *p;
    loff_t off = 0;

    printk("nvme_seq_start\n");
    list_for_each_entry(p, &nvme_event_list, list) {
        if (*pos == off++) return p;
    }
    return NULL;
}

static void *nvme_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
    struct list_head *n = ((struct nvme_data *) v)->list.next;
    ++*pos;
    printk("nvme_seq_next %llx\n", *pos);
    return (n != &nvme_event_list) ?
        list_entry(n, struct nvme_data, list) : NULL;
}

static int nvme_seq_show(struct seq_file *seq, void *v)
{
    const struct nvme_data *p = (struct nvme_data *) v;
    seq_printf(seq, p->info);
    return 0;
}

static void nvme_seq_stop(struct seq_file *seq, void *v)
{
    struct nvme_data *p = (struct nvme_data *) v;
    if (p) {
        list_del(&p->list);
        kfree(p);
    }
    printk("nvme_seq_stop\n");
}

static struct seq_operations nvme_seq_ops = {
    .start = nvme_seq_start,
    .next  = nvme_seq_next,
    .stop  = nvme_seq_stop,
    .show  = nvme_seq_show,
};

static int nvme_seq_open(struct inode *inode, struct file *file)
{
    printk("nvme_seq_open\n");
    dummy();
    return seq_open(file, &nvme_seq_ops);
}

static struct file_operations nvme_proc_fps = {
    .owner   = THIS_MODULE,
    .open    = nvme_seq_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = seq_release,
};

static int nvme_init(void)
{
    static struct proc_dir_entry *entry;

    printk("nvme_stat loaded...\n");
    entry = create_proc_entry("nvme_stat", S_IWUSR, NULL);
    if (entry) {
        printk("create_proc_entry succeeded!\n");
        entry->proc_fops = &nvme_proc_fps;
    } else {
        printk("create_proc_entry failed!\n");
    }

    return 0;
}

static void nvme_exit(void)
{
    printk("unloading nvme_stat...\n");
    remove_proc_entry("nvme_stat",NULL);
}

module_init(nvme_init);
module_exit(nvme_exit);
MODULE_LICENSE("GPL");

