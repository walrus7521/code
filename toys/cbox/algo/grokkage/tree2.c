#include <stdio.h>
#include <stdlib.h>

typedef int key_t;

typedef struct tr_n_t {
    key_t key;
    struct tr_n_t *left, *right;
} tree_node_t;
typedef tree_node_t object_t;

/* utilities
 */
void tshow(tree_node_t *tree) 
{
    if (tree) {
        tshow(tree->left);
        printf("v: %d\n", tree->key);
        tshow(tree->right);
    }       
}

#define MAX_DEPTH 16
int _print_t(tree_node_t *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
    //sprintf(b, "(%c)", tree->key);
    left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    } else if (depth && !is_left) {
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    }
    return left + width + right;
}

int print_t(tree_node_t *tree)
{
    char s[MAX_DEPTH][255];
    int i;
    for (i = 0; i < MAX_DEPTH; i++)
        sprintf(s[i], "%80s", " ");
    _print_t(tree, 0, 0, 0, s);
    for (i = 0; i < MAX_DEPTH; i++)
        printf("%s\n", s[i]);
    return 0;
}



void left_rotation(tree_node_t *tree);
void right_rotation(tree_node_t *tree);


void return_node(tree_node_t tree)
{
    // complicated iteration and free
}

tree_node_t *get_node() {
    tree_node_t *t = (tree_node_t *) malloc(sizeof(tree_node_t));
    t->left = t->right = NULL;
    return t;
}

void left_rotation(tree_node_t *n)
{
    tree_node_t  *tmp_node;
    int tmp_key;
    tmp_node = n->left;
    tmp_key = n->key;
    n->left = n->right;
    n->key = n->right->key;
    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left = tmp_node;
    n->left->key = tmp_key;
}

void right_rotation(tree_node_t *n)
{
    tree_node_t  *tmp_node;
    int tmp_key;
    tmp_node = n->right;
    tmp_key = n->key;
    n->right = n->left;
    n->key = n->left->key;
    n->left = n->right->left;
    n->right->left = n->right->right;
    n->right->right = tmp_node;
    n->right->key = tmp_key;
}

int insert(tree_node_t *tree, int new_key, object_t *new_object)
{
    tree_node_t *tmp_node;
    printf("insert: %d\n", new_key);
    if (tree->left == NULL) {
        // we have an empty tree
        tree->left = (tree_node_t *) new_object;
        tree->key = new_key;
        tree->right = NULL;
    }
    else {
        tmp_node = tree;
        while (tmp_node->right != NULL) {
            if (new_key < tmp_node->key) 
                tmp_node = tmp_node->left;
            else 
                tmp_node = tmp_node->right;
        }
        /* found candidate lear. Test whether key distinct */
        if (tmp_node->key == new_key) return (-1); // no dups
        /* key is distinct, perform insert */
        else {
            // we are at a leaf, right node is NULL
            tree_node_t *old_leaf, *new_leaf;
            old_leaf = get_node();
            old_leaf->left = tmp_node->left;
            old_leaf->key = tmp_node->key;
            old_leaf->right = NULL;
            new_leaf = get_node();
            new_leaf->left = (tree_node_t *) new_object;
            new_leaf->key = new_key;
            new_leaf->right = NULL;
            if (new_key < tmp_node->key) {
                tmp_node->left = old_leaf;
                tmp_node->right = new_leaf;
                tmp_node->key = new_key;
            } else {
                tmp_node->left = new_leaf;
                tmp_node->right = old_leaf;
            }
        }
    }
    return 0;
}

object_t *find(tree_node_t *tree,
                key_t query_key)
{
    tree_node_t *tmp_node;
    if (tree->left == NULL) 
        return (NULL);
    else 
    if (tree->right == NULL) {
        // we have a leaf
        if (tree->left->key == query_key) {
            return (object_t*) tree->left;
        }
    }
    else {
        // we have subtrees
        tmp_node = tree;
        while (tmp_node->right != NULL) {
            if (query_key < tmp_node->key)  
                tmp_node = tmp_node->left;
            else 
                tmp_node = tmp_node->right;
            if (tmp_node->key == query_key) 
                return (object_t*) tmp_node->left;
            //else return (NULL);
        }
    }
    return (NULL);
}

int main()
{
    tree_node_t *tree = NULL, *t;
    object_t *obj;

    int a[] = {10, 5, 4, 3, 4, 7, 16, 13, 11, 13, 20, 18, 17, 16, 17, 19, 30};
    int i, sz = sizeof(a) / sizeof(a[0]);
    tree = get_node();
    for (i = 0; i < sz; ++i) {
        tree_node_t *new_object = get_node();
        if (insert(tree, a[i], new_object) < 0) {
            printf("error inserting\n");
        }
    }
    print_t(tree);
    for (int i = 0; i < sz; i++) {
        obj = find(tree, i);
        if (obj) printf("found: %d\n", obj->key);
    }
    //obj = find(tree, 30);
    //if (obj) printf("found: %d\n", obj->key);


    return 0;
}

