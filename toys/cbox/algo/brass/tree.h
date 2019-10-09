#ifndef __TREE__
#define __TREE__

typedef int key_t;

typedef struct tr_n_t {
    key_t key;
    struct tr_n_t *left, *right;
} tree_node_t;

typedef struct _object_t {
    char payload;
} object_t;

void return_node(tree_node_t *tree);
tree_node_t *get_node();
tree_node_t *create_tree(void);
void left_rotation(tree_node_t *n);
void right_rotation(tree_node_t *n);
int insert(tree_node_t *tree, int new_key, object_t *new_object);
object_t *delete(tree_node_t *tree, key_t delete_key);
object_t *find(tree_node_t *tree, key_t query_key);
tree_node_t *interval_find(tree_node_t *tree, key_t a, key_t b);
tree_node_t *make_list(tree_node_t *tree);

void test_tree();

#endif
