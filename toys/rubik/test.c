#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tree.h"

void test_tree()
{
    tree_node_t *search_tree = NULL;
    tree_node_t *search_tree_clone = NULL;
    tree_node_t *interval;
    tree_node_t *result_list;
    object_t *obj;

    int a[] = {10, 5, 4, 3, 4, 7, 16, 13, 11, 13, 20, 18, 17, 16, 17, 19, 30};
    int i, sz = sizeof(a) / sizeof(a[0]);

    printf("data: ");
    for (i = 0; i < sz; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");

    search_tree = create_tree();
    search_tree_clone = create_tree();
    //search_tree_clone = search_tree;

    for (i = 0; i < sz; ++i) {
        object_t *new_object = (object_t *) malloc(sizeof(object_t));
        new_object->payload = 'a'+i;
        if (insert(search_tree, a[i], new_object) < 0) {
            printf("error inserting: %c\n", new_object->payload);
            free(new_object);
        }
        object_t *new_object_clone = (object_t *) malloc(sizeof(object_t));
        new_object_clone->payload = 'a'+i;
        if (insert(search_tree_clone, a[i], new_object_clone) < 0) {
            printf("error inserting clone: %c\n", new_object_clone->payload);
            free(new_object_clone);
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

    printf("make a list\n");
    // make_list will muck up the tree links - @fixit
    result_list = make_list(search_tree_clone);
    while (result_list) {
        tree_node_t *tmp = result_list;
        obj = (object_t *) result_list->left;
        printf("(%d %c), ", result_list->key, obj->payload);
        result_list = result_list->right;
        free(tmp);
    }
    printf("\n");

    for (i = 0; i < sz; i++) {
        obj = delete_tree(search_tree, a[i]);
        if (obj) printf("deleted[%d] : %02d %c\n", i, a[i], obj->payload);
        //else     printf("not deleted: %02d\n", a[i]);
    }
    remove_tree(search_tree);
    search_tree = NULL;

}

void test_stack()
{
    int size = 8;
    int i;
    tstack_t *st = create_stack(size);
    for (i = 0; i < size; i++) {
        push((item_t) i, st);
    }
    while (!stack_empty(st)) {
        item_t t = pop(st);
        printf("item: %d\n", t);
    }
}

void test_queue()
{
    int size = 8;
    int i;
    queue_t *qu = create_queue();
    for (i = 0; i < size; i++) {
        enqueue((item_t) i, qu);
    }
    printf("forward\n");
    show_queue(qu);
    qu->remove = reverse_queue(qu);
    printf("reverse\n");
    show_queue(qu);
/*
    while (!queue_empty(qu)) {
        item_t t = dequeue(qu);
        printf("item: %d\n", (int) t);
    }
*/
}

void test_list()
{
    //l->next = list_reverse_pqr(l);

}

int main()
{
    test_stack();
    //test_queue();
    //test_tree();

    return 0;
}
