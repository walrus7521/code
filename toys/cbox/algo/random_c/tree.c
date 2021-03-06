#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

void bad_print_tree(tree_node_t *tree)
{  
    tree_node_t *current_node, *tmp;
    if (tree == NULL) return;
    if( tree->left == NULL ) {
        printf("root: %d\n", tree->key);
    } else {  
        current_node = tree;
        while (current_node->right != NULL ) {  
            if (current_node->left->right == NULL) {  
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

void return_node(tree_node_t *node)
{
    free(node);
}

tree_node_t *get_node()
{
    tree_node_t *t = (tree_node_t *) malloc(sizeof(tree_node_t));
    return t;
}

tree_node_t *create_tree(void)
{
    tree_node_t *tmp_node;
    tmp_node = get_node();
    tmp_node->left = NULL;
    return (tmp_node);
}

/*
 * This essentially performs rotations in the root till the left-lower neighbor is
 * a leaf; then it returns that leaf, moves the root down to the right, and returns the
 * previous root
 */
void remove_tree(tree_node_t *tree)
{ 
    tree_node_t *current_node, *tmp;
    if (tree->left == NULL) {
        return_node(tree);
    } else {
        current_node = tree;
        while (current_node->right != NULL) {
            if (current_node->left->right == NULL) {
                return_node(current_node->left);
                tmp = current_node->right;
                return_node(current_node);
                current_node = tmp;
            } else {
                tmp = current_node->left;
                current_node->left = tmp->right;
                tmp->right = current_node;
                current_node = tmp;
            }
        }
        return_node(current_node);
    }
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

/* Node: if key exists, n->key has the key and n->left the object
 * containing the information for that key
 *
 * The insert operation starts out the same as the find, but after it finds the
 * correct place to insert the new object, it has to create a new interior node and
 * a new leaf node and put them in the tree. We assume, as always, that there are
 * functions get node and return node available, as described in Section 1.4.
 * For the moment we assume all the keys are unique and treat it as an error if there
 * is already an object with that key in the tree; but in many practical applications
 * we need to deal with multiple objects of the same key (see Section 2.6). *
 */
int insert(tree_node_t *tree, int new_key, object_t *new_object)
{
    tree_node_t *tmp_node;
    if (tree->left == NULL) { // empty tree
        // we have an empty tree
        tree->left = (tree_node_t *) new_object;
        tree->key = new_key;
        tree->right = NULL;
    } else {
        // same as find
        tmp_node = tree;
        while (tmp_node->right != NULL) {
            if (new_key < tmp_node->key) 
                tmp_node = tmp_node->left;
            else 
                tmp_node = tmp_node->right;
        }
        /* found candidate lear. Test whether key distinct */
        if (tmp_node->key == new_key) {
            return (-1); // no dups
        /* key is distinct, perform insert */
        } else {
            // tmp_node is a leaf
            tree_node_t *old_leaf, *new_leaf;
            old_leaf = get_node();              // copy of old leaf
            old_leaf->left = tmp_node->left;
            old_leaf->key = tmp_node->key;
            old_leaf->right = NULL;
            new_leaf = get_node();              // new leaf
            new_leaf->left = (tree_node_t *) new_object;
            new_leaf->key = new_key;
            new_leaf->right = NULL;
            if (tmp_node->key < new_key) {  // only modify the old leaf node
                tmp_node->left = old_leaf;  // old leaf goes left (new key > old_key)
                tmp_node->right = new_leaf; // new leaf goes right
                tmp_node->key = new_key;    // new key is larger, so replace
            } else {
                tmp_node->left = new_leaf;  // new leaf goes left (new_key <= old_key)
                tmp_node->right = old_leaf; // old leaf goes right
            }
        }
    }
    return 0;
}

/*
 * The delete operation is even more complicated because when we are deleting
 * a leaf, we must also delete an interior node above the leaf. For this, we need
 * to keep track of the current node and its upper neighbor while going down in
 * the tree. Also, this operation can lead to an error if there is no object with the
 * given key. 
 *
 * If there is additional information in the nodes, it must also be copied or
 * updated when we copy the content of the other node into the upper node.
 * Note that we delete the nodes, but not the object itself. There might be other
 * references to this object. But if this is the only reference to the object, this will
 * cause a memory leak, so we should delete the object. This is the responsibility
 * of the user, so we return a pointer to the object.
 */
object_t *delete_tree(tree_node_t *tree, key_t delete_key)
{ 
    tree_node_t *tmp_node, *upper_node, *other_node;
    object_t *deleted_object;
    if (tree->left == NULL) {
        return( NULL );
    } else if (tree->right == NULL) { 
        if (tree->key == delete_key) { 
            deleted_object = (object_t *) tree->left;
            tree->left = NULL;
            return (deleted_object);
        } else {
            return (NULL);
        }
    } else { 
        tmp_node = tree;
        while (tmp_node->right != NULL) { 
            upper_node = tmp_node;
            if (delete_key < tmp_node->key) {
                tmp_node = upper_node->left;
                other_node = upper_node->right;
            } else { 
                tmp_node = upper_node->right;
                other_node = upper_node->left;
            }
        }
        if (tmp_node->key != delete_key) {
            return( NULL );
        } else { 
            upper_node->key = other_node->key;
            upper_node->left = other_node->left;
            upper_node->right = other_node->right;
            deleted_object = (object_t *) tmp_node->left;
            return_node(tmp_node);
            return_node(other_node);
            return (deleted_object);
        }
    }
}

object_t *find(tree_node_t *tree, key_t query_key)
{
    tree_node_t *tmp_node;
    if (tree->left == NULL) { // empty tree
        return (NULL);
    } else {
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

/* this trashes the list -- make a clone first */
tree_node_t *make_list(tree_node_t *tree)
{ 
    int size_stack = 100;
    tree_node_t *list, *node;
    if (tree->left == NULL)
    { 
        return_node(tree);
        return (NULL);
    } else {
        tstack_t *st = create_stack(size_stack);
        push(tree, st);
        list = NULL;
        while (!stack_empty(st)) {
            node = (tree_node_t *) pop(st);
            if (node->right == NULL) {
                node->right = list;
                list = node;
            } else { 
                push(node->left, st);
                push(node->right, st);
                return_node(node);
            }
        }
        return(list);
    }
}

tree_node_t *interval_find(tree_node_t *tree, key_t a, key_t b)
{
    tree_node_t *tr_node;
    tree_node_t *result_list, *tmp;
    result_list = NULL;
    int size_stack = 16;
    tstack_t *st = create_stack(size_stack);
    push((item_t) tree, st);

    printf("interval find: %d %d\n", a, b);
    while (!stack_empty(st)) { 
        tr_node = (tree_node_t *) pop(st);
        if( tr_node->right == NULL ) { /* reached leaf, now test */
            if( a <= tr_node->key && tr_node->key < b ) { 
                //printf("adding: %d\n", tr_node->key);
                tmp = get_node();
                /* leaf key in interval */
                tmp->key = tr_node->key; /*
                copy to output list */
                tmp->left = tr_node->left;
                tmp->right = result_list;
                result_list = tmp;
            }
        /* not leaf, might have to follow down */ 
        } else if (b <= tr_node->key) {
            /* entire interval left */
            push(tr_node->left, st);
        } else if (tr_node->key <= a ) {
            /* entire interval right */
            push( tr_node->right, st);
        } else { /* node key in interval, follow left and right */
            push( tr_node->left, st);
            push( tr_node->right, st);
        }
    }
    remove_stack(st);

    return (result_list);
}

