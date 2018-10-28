#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN (2)
#define MAX (4)

#define FMT         ("%d - ")
#define FMT_FULL    ("found [%d] => %d\n")

typedef char key_t;

typedef struct {
    key_t key;
    uint32_t value;
    char name[12];
} treeentry_t;

bool trace = false;

typedef struct treenode {
    treeentry_t entry;
    bool red;
    struct treenode *left, *right;
} treenode_t;

typedef enum {
    OK,         // the color of current root/subtree has not changed, RB property satisfied
    REDNODE,    // current root changed from black to red, may need modifying
    RIGHTRED,   // current root and right child are both red, flip or rotate
    LEFTRED     // current root and left child are both red, flip or rotate
} outcome_t;

bool search_node(key_t target, treenode_t *current, int *pos);

treenode_t *new_node(treeentry_t newentry, outcome_t *status)
{
    treenode_t *new = (treenode_t *) malloc(sizeof(treenode_t));
    new->entry = newentry;
    new->red = true;
    new->left = new->right = NULL;
    *status = REDNODE;
    return new;
}

void flip_color(treenode_t **current, outcome_t *status)
{
}

void rotate_right(treenode_t **current, outcome_t *status)
{
}

void rotate_left(treenode_t **current, outcome_t *status)
{
}

void d_rotate_right(treenode_t **current, outcome_t *status)
{
}

void d_rotate_left(treenode_t **current, outcome_t *status)
{
}


void modify_left(treenode_t **current, outcome_t *status)
{
    switch (*status) {
        case OK:    // no action needed
            break;
        case REDNODE:
            if ((*current)->red) {
                *status = LEFTRED;
            } else {
                *status = OK;
            }
            break;
        case LEFTRED:
            if (!(*current)->right) {
                rotate_right(current, status);
            } else if ((*current)->right->red) {
                flip_color(current, status);
            } else {
                rotate_right(current, status);
            }
            break;
        case RIGHTRED:
            if (!(*current)->right) {
                d_rotate_right(current, status);
            } else if ((*current)->right->red) {
                flip_color(current, status);
            } else {
                d_rotate_right(current, status);
            }
            break;
    }
}

void modify_right(treenode_t **current, outcome_t *status)
{
}

void rec_insert(treenode_t **current, treeentry_t newentry, outcome_t *status)
{
    if (!(*current)) {
        *current = new_node(newentry, status);
    } else if (newentry.key < (*current)->entry.key) {
        rec_insert(&(*current)->left, newentry, status);
        modify_left(current, status);
    } else if (newentry.key > (*current)->entry.key) {
        rec_insert(&(*current)->right, newentry, status);
        modify_right(current, status);
    } else {
        printf("warning: duplicate key inserted.\n");
    }
}

treenode_t *insert(treeentry_t newentry, treenode_t *root)
{
    outcome_t status;
    rec_insert(&root, newentry, &status);
    if (status == REDNODE) {
        // always split the root and keep it black
        root->red = false;
    } else if (status != OK) {
        printf("error: insertion with bad red-black status at root.\n");
    }

    return root;
}

treenode_t *search_tree(key_t target, treenode_t *root, int *targetpos)
{
    return NULL;
}

int main()
{
    treeentry_t e;
    int i;
    treenode_t *root = malloc(sizeof(treenode_t));
    memset(root, 0, sizeof(treenode_t));

    key_t a[] = {1,3,5,7,2,4,6,8};
    char *names[] = {"bart", "cindy", "grant", "claire", "mackenzie", "taylor", "kevin", "alusia"};
    int len = sizeof(a) / sizeof(a[0]);

    for (i = 0; i < len; i++) {
        e.key = a[i];
        e.value = 42;
        strcpy(e.name, names[i]);
        root = insert(e, root);
    }
    //show_nodes(root, 0);
    //show_tree_bfs(root);

    int targetpos = 0;
    for (i = 0; i < len; i++) {
        targetpos = 0;
        treenode_t *s = search_tree(a[i], root, &targetpos);
        //if (s) printf("found [%d] => %c\n", targetpos, s->entry[targetpos].key);
        //if (s) print_record(&s->entry);
    }
}

