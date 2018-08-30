#include <linux/module.h>
#include <linux/slab.h>
#include "../toys/hash64x.h"

enum { NHASH = 32768 };
hashtable *my_hash;
static int __init hash64x_test_init(void)
{   
    int i;    
    printk("hash64x_test: yo wusup\n");
    my_hash = hash_create(NHASH);
    for (i = 0; i < 8; i++) {
        hash_set(my_hash, i, (void*) NULL);
    }
    hash_dump(my_hash);
    return 0;
}

static void __exit hash64x_test_exit(void)
{   
    hash_destroy(my_hash);    
    printk("hash64x_test: buh bye\n");
}

module_init(hash64x_test_init);
module_exit(hash64x_test_exit);
MODULE_LICENSE("GPL");

