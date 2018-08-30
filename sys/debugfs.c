/*
 *
 * https://lwn.net/Articles/115405/
 * http://www.cs.montana.edu/courses/309/topics/4-disks/debugfs_example.html
 * http://opensourceforu.efytimes.com/2010/10/debugging-linux-kernel-with-debugfs/
 *
 * root@bart-dev:/home/bart/src/repo/utils/sys# ll /sys/kernel/debug/dell/
 * total 0
 * drwxr-xr-x  2 root root 0 Oct 13 13:13 ./
 * drwx------ 35 root root 0 Oct 13 13:13 ../
 * -rw-r--r--  1 root root 0 Oct 13 13:13 hexnum
 * -rw-r--r--  1 root root 0 Oct 13 13:13 number
 * -rw-r--r--  1 root root 0 Oct 13 13:13 text
 *
 */
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/debugfs.h> /* this is for DebugFS libraries */ 
#include <linux/fs.h>   

#define len 200 
u64 intvalue,hexvalue; 
struct dentry *dirret,*fileret,*u64int,*u64hex; 
char ker_buf[len]; 
int filevalue; 

/* read file operation */
static ssize_t myreader(struct file *fp, char __user *user_buffer, 
                                size_t count, loff_t *position) 
{ 
     return simple_read_from_buffer(user_buffer, count, position, ker_buf, len);
} 
 
/* write file operation */
static ssize_t mywriter(struct file *fp, const char __user *user_buffer, 
                                size_t count, loff_t *position) 
{ 
        if(count > len ) 
                return -EINVAL; 
  
        return simple_write_to_buffer(ker_buf, len, position, user_buffer, count); 
} 
 
static const struct file_operations fops_debug = { 
        .read = myreader, 
        .write = mywriter, 
}; 
 
static int __init init_debug(void) 
{ 
    /* create a directory by the name dell in /sys/kernel/debugfs */
    dirret = debugfs_create_dir("dell", NULL); 
      
    /* create a file in the above directory 
    This requires read and write file operations */
    fileret = debugfs_create_file("text", 0644, dirret, &filevalue, &fops_debug);
 
    /* create a file which takes in a int(64) value */
    u64int = debugfs_create_u64("number", 0644, dirret, &intvalue); 
    if (!u64int) { 
        printk("error creating int file"); 
        return (-ENODEV); 
    } 
    /* takes a hex decimal value */
    u64hex = debugfs_create_x64("hexnum", 0644, dirret, &hexvalue ); 
    if (!u64hex) { 
        printk("error creating hex file"); 
        return (-ENODEV); 
    } 
 
    return (0); 
} 
 
static void __exit exit_debug(void) 
{ 
    /* removing the directory recursively which 
    in turn cleans all the file */
    debugfs_remove_recursive(dirret); 
} 

module_init(init_debug); 
module_exit(exit_debug);

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Surya Prabhakar <surya_prabhakar@dell.com>"); 
MODULE_DESCRIPTION("sample code for DebugFS functionality"); 

