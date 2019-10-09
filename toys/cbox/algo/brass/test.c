#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tree.h"

void test_tree()
{
    tree_node_t *search_tree = NULL;
    tree_node_t *interval;
    object_t *obj;

    int a[] = {10, 5, 4, 3, 4, 7, 16, 13, 11, 13, 20, 18, 17, 16, 17, 19, 30};
    int i, sz = sizeof(a) / sizeof(a[0]);
    search_tree = create_tree();
    for (i = 0; i < sz; ++i) {
        object_t *new_object = (object_t *) malloc(sizeof(object_t));
        new_object->payload = 'a'+i;
        if (insert(search_tree, a[i], new_object) < 0) {
            printf("error inserting: %c\n", new_object->payload);
            free(new_object);
        }
    }

    interval = interval_find(search_tree, 10, 30);
    while (interval) {
        tree_node_t *tmp = interval;
        obj = (object_t *) interval->left;
        printf("interval found %d %c\n", interval->key, obj->payload);
        interval = interval->right;
        free(tmp);
    }

    for (i = 0; i < sz; i++) {
        obj = find(search_tree, a[i]);
        if (obj) printf("found      : %02d %c\n", a[i], obj->payload);
        else     printf("not found  : %02d\n", a[i]);
    }

    //print_tree(search_tree);

    for (i = 0; i < sz; i++) {
        obj = delete(search_tree, a[i]);
        if (obj) printf("deleted    : %02d %c\n", a[i], obj->payload);
        //else     printf("not deleted: %02d\n", a[i]);
    }
    free(search_tree); search_tree = NULL;

}

void test_stack()
{
    int size = 8;
    int i;
    stack_t *st = create_stack(size);
    for (i = 0; i < size; i++) {
        push((item_t) i, st);
    }
    while (!stack_empty(st)) {
        item_t t = pop(st);
        printf("item: %d\n", (int) t);
    }
}

int main()
{
    //test_stack();
    test_tree();

    return 0;
}
