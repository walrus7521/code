/* work derived from K&R */
#include <linux/module.h>
#include <linux/pci.h>
#include "hash64x.h"

hashtable *hash_create(unsigned int buckets)
{
    struct list_head *symlist;
    hashtable *hash;
    int i;
    hash = (hashtable *) kzalloc(sizeof(hashtable), GFP_KERNEL);
    symlist = (struct list_head *) kzalloc(buckets * sizeof(struct list_head), GFP_KERNEL);
    hash->symlist = symlist;
    hash->buckets = buckets;
    for (i = 0; i < (int) buckets; i++) {
        INIT_LIST_HEAD(&hash->symlist[i]);
    }
    printk("create [%x] buckets\n", hash->buckets);
    return hash;
}

void hash_destroy(hashtable *hashtab)
{
    int h;
    pair *sym, *next;
    for (h = 0; h < hashtab->buckets; h++) {
        list_for_each_entry_safe(sym, next, &hashtab->symlist[h], entry) {
            printk("destroy [%llx] => %p\n", sym->key, sym->value);
            list_del(&sym->entry);
            kfree(sym);
        }
    }
}

static unsigned int hash(u64 key, unsigned int buckets)
{
    u32 slot = hash32(key) % buckets;
    return slot;
}

static pair* lookup(hashtable *hashtab, u64 key, int create, void *value)
{
    int h;
    pair *sym = NULL, *next = NULL;
    h = hash(key, hashtab->buckets);
    if (!list_empty(&hashtab->symlist[h])) {
        list_for_each_entry_safe(sym, next, &hashtab->symlist[h], entry) {
            if (key == sym->key) {
                printk("found %p -> %llx\n", sym->value, sym->key);
                return sym;
            }
        }
    }
    if (create) {
        sym = (pair *) kzalloc(sizeof(pair), GFP_KERNEL);
        sym->key = key;
        sym->value = value;
        list_add(&sym->entry, &hashtab->symlist[h]);
        printk("create [%llx] => %p\n", sym->key, sym->value);
    }
    return sym;
}

int hash_find(hashtable *hashtab, u64 key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return (sym != NULL) ? 1 : 0;
}

pair *hash_get(hashtable *hashtab, u64 key)
{
    pair *sym = lookup(hashtab, key, 0, 0);
    return sym;
}

void hash_set(hashtable *hashtab, u64 key, void *value)
{
    pair *sym = lookup(hashtab, key, 1, value);
    if (sym) sym->value = value;
}

void hash_dump(hashtable *hashtab)
{
    int h;
    pair *sym, *next;
    for (h = 0; h < hashtab->buckets; h++) {
        list_for_each_entry_safe(sym, next, &hashtab->symlist[h], entry) {
            printk("[%llx] => %p\n", sym->key, sym->value);
        }
    }
}

