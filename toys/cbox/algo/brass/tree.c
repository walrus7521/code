#include <stdio.h>
#include <stdlib.h>

typedef int key_t;

typedef struct tr_n_t {
    key_t key;
    struct tr_n_t *left, *right;
    char info;
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

void print_tree(tree_node_t *tree)
{  
    tree_node_t *current_node, *tmp;
    if( tree->left == NULL )
        printf("root: %d\n", tree->key);
    else
    {  
        current_node = tree;
        while(current_node->right != NULL ) {  
            if( current_node->left->right == NULL ) {  
                printf("left : %d\n", current_node->left->key);
                tmp = current_node->right;
                printf("right: %d\n", current_node->right->key);
                current_node = tmp;
            } else {  
                tmp = current_node->left;
                current_node->left = tmp->right;
                tmp->right = current_node; 
                current_node = tmp;
            }
        }
        printf("root2: %d\n", current_node->key);
    }
}



void left_rotation(tree_node_t *tree);
void right_rotation(tree_node_t *tree);


void return_node(tree_node_t tree)
{
    // complicated iteration and free
}

tree_node_t *get_node() {
    tree_node_t *t = (tree_node_t *) malloc(sizeof(tree_node_t));
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

tree_node_t *create_tree(void)
{
    tree_node_t *tmp_node;
    tmp_node = get_node();
    tmp_node->left = NULL;
    return (tmp_node);
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

/* Node: if key exists, n->key has the key and n->left the object
 * containing the information for that key
 */
int insert(tree_node_t *tree, int new_key, object_t *new_object)
{
    tree_node_t *tmp_node;
    //printf("insert: %d\n", new_key);
    if (tree->left == NULL) {
        // we have an empty tree
        //printf("insert new\n");
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
            if (tmp_node->key < new_key) {
                tmp_node->left = old_leaf;
                tmp_node->right = new_leaf;
                tmp_node->key = new_key;
            } else {
                tmp_node->left = new_leaf;
                tmp_node->right = old_leaf;
            }
            //printf("inserted: %d\n", new_key);
        }
    }
    return 0;
}

object_t *find(tree_node_t *tree, key_t query_key)
{
    tree_node_t *tmp_node;
    if (tree->left == NULL)
        return (NULL);
    else {
        tmp_node = tree;
        while (tmp_node->right != NULL) {
            if (query_key < tmp_node->key) {
                tmp_node = tmp_node->left;
            } else {
                tmp_node = tmp_node->right;
            }
        }
        if (tmp_node->key == query_key) {
            return (object_t *) tmp_node->left;
        } else {
            return (NULL);
        }
    }
    return (NULL);
}

object_t *find_old(tree_node_t *tree, key_t query_key)
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
    tree_node_t *search_tree = NULL, *t;
    object_t *obj;

    int a[] = {10, 5, 4, 3, 4, 7, 16, 13, 11, 13, 20, 18, 17, 16, 17, 19, 30};
    int i, sz = sizeof(a) / sizeof(a[0]);
    search_tree = create_tree();
    for (i = 0; i < sz; ++i) {
        tree_node_t *new_object = get_node();
        new_object->info = 'a'+i;
        if (insert(search_tree, a[i], new_object) < 0) {
            printf("error inserting\n");
        }
    }

    for (int i = 0; i < sz; i++) {
        obj = find(search_tree, a[i]);
        if (obj) printf("found: %d %c\n", a[i], ((tree_node_t*)(obj))->info);
        else printf("not found: %d\n", a[i]);
    }

    print_tree(search_tree);

    return 0;
}

