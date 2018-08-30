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
    int count;
    treeentry_t entry[MAX+1]; // 1-based
    struct treenode *branch[MAX+1]; // zero-based
} treenode_t;

bool search_node(key_t target, treenode_t *current, int *pos);

void init(treenode_t *root)
{
    int i;
    root->count = 0;
    for (i = 0; i < MAX+1; i++) {
        root->entry[i].key = -1;
        root->branch[i] = NULL;
    }
}

void push_in(treeentry_t medentry, treenode_t *medright, treenode_t *current, int pos)
{
    int i;
    for (i = current->count; i > pos; i--) {
        // shift all keys and branches to the right
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
}

void split(treeentry_t medentry, treenode_t *medright, treenode_t *current, int pos,
           treeentry_t *newmedian, treenode_t **newright)
{
    int i;      // used for copying from *current to new node
    int median; // median position in the combined, overfull node
    if (pos <= MIN) median = MIN;
    else            median = MIN+1;
    // get a new node and put it on the right
    *newright = (treenode_t *) malloc(sizeof(treenode_t));
    init(*newright);
    for (i = median+1; i <= MAX; i++) {
        (*newright)->entry[i-median] = current->entry[i];
        (*newright)->branch[i-median] = current->branch[i];
    }
    (*newright)->count = MAX - median;
    current->count = median;
    if (pos <= MIN) push_in(medentry, medright, current, pos);
    else            push_in(medentry, medright, *newright, pos-median);
    *newmedian = current->entry[current->count];
    (*newright)->branch[0] = current->branch[current->count];
    current->count--;
}

bool push_down(treeentry_t newentry, treenode_t *current,
               treeentry_t *medentry, treenode_t **medright)
{
    int pos;
    //printf("push: %p\n", current);
    if (current == NULL) { // empty tree, done
        //printf("null root\n");
        *medentry = newentry;
        *medright = NULL;
        return true;
    } else {
        if (search_node(newentry.key, current, &pos)) {
            printf("warning: inserting duplicate key %d\n", newentry.key);
        }
        if (push_down(newentry, current->branch[pos], medentry, medright)) {
            if (current->count < MAX) {
                //printf("pushing in at %d\n", pos);
                push_in(*medentry, *medright, current, pos);
                return false;
            } else {
                //printf("splitting at %d\n", pos);
                split(*medentry, *medright, current, pos, medentry, medright);
                return true;
            }
        }
        //printf("fell through\n");
        return false;
    }
}

treenode_t *insert(treeentry_t newentry, treenode_t *root)
{
    treeentry_t medentry; // potential new root
    treenode_t *medright; // right of medentry
    treenode_t *newroot;  // used to increase height
    //printf("insert: %c => %p\n", newentry.key, root);
    if (push_down(newentry, root, &medentry, &medright)) {
        //printf("grow in height\n");
        newroot = (treenode_t *) malloc(sizeof(treenode_t));
        init(newroot);
        newroot->count = 1;
        newroot->entry[1] = medentry; // key
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        return newroot;
    }
    return root;
}

bool search_node(key_t target, treenode_t *current, int *pos)
{
    //printf("search node: %d\n", target);
    if (target < current->entry[1].key) { // go left
        //printf("go left\n");
        *pos = 0;
        return false;
    } else {
        //printf("linear search - start at %d\n", current->count);
        for (*pos = current->count; target < current->entry[*pos].key && *pos > 1; (*pos)--) ;
        //printf("linear search - end at [%d] = %d\n", *pos, current->entry[*pos].key);
        return (target == current->entry[*pos].key);
    }
}

treenode_t *search_tree(key_t target, treenode_t *root, int *targetpos)
{
    if (!root) return NULL;

    else if (search_node(target, root, targetpos))
        return root;

    else
        return search_tree(target, root->branch[*targetpos], targetpos);
}

treenode_t *visited[64];
uint8_t  ptr = 0;
bool seen(treenode_t *root)
{
    int i;
    for (i = 0; i < ptr; i++) {
        if (visited[i] == root) return true;
    }
    visited[ptr++] = root;
    return false;
}

void show_nodes(treenode_t *root, int level)
{
    int i;
    if (root == NULL) return;
    //printf("show_nodes: %d, level: %d\n", root->count, level);
    seen(root);
    printf("L:%d:%p]  ", level, root);
    //for (i = 1; i <= root->count; i++) printf("%c - ", root->entry[i].key);
    for (i = 1; i <= root->count; i++) printf("%d - ", root->entry[i].key);
    printf("\n");
    for (i = 0; i < MAX; i++) {
        if (!seen(root->branch[i])) {
            show_nodes(root->branch[i], level+1);
        }
    }
}

void print_record(treeentry_t *entry)
{
    printf("key:   %d\n", entry->key);
    printf("value: %d\n", entry->value);
    printf("name:  %s\n", entry->name);
    printf("\n");
}

void show_nodey(treenode_t *node)
{
    for (int i = 1; i <= node->count; i++) {
        print_record(&node->entry[i]);
    }
}

treenode_t *queue[64];
uint32_t qhead = 0;
uint32_t qtail = 0;
void show_tree_bfs(treenode_t *root)
{
    queue[qhead++] = root;
    seen(root);
    while (qhead != qtail) {
        treenode_t *t = queue[qtail++];
        show_nodey(t);
        for (int i = 0; i <= MAX; i++) {
            if (t->branch[i] != NULL && !seen(t->branch[i])) {
                queue[qhead++] = t->branch[i];
            }
        }
    }
}

uint32_t hash_string(const char * s)
{
    uint32_t hash = 0;
    for(; *s; ++s) {
        hash += *s;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
#define HASH_MAX (25307)
    return hash % HASH_MAX;
}

int main()
{
    treeentry_t e;
    int i;
    treenode_t *root = malloc(sizeof(treenode_t));
    memset(root, 0, sizeof(treenode_t));
    init(root);

    //key_t a[] = "agfbkdhmjesirxclntupzyoqvw";
    //int len = strlen(a);
    key_t a[] = {1,3,5,7,2,4,6,8};
    char *names[] = {"bart", "cindy", "grant", "claire", "mackenzie", "taylor", "kevin", "alusia"};
    int len = sizeof(a) / sizeof(a[0]);

    for (i = 0; i < len; i++) {
        e.key = a[i];
        e.value = hash_string(names[i]);
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
        if (s) print_record(&s->entry[targetpos]);
    }
}

