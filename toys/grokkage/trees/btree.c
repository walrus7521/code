#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dprint(...)  {} //printf

#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

#define ORDER (5)

#define MAX (ORDER-1)
#define MIN (MAX/2)

#define DUMMY ('Z')

typedef char /* int */ Key;

typedef struct treeentry Treeentry;
struct treeentry {
    Key key;
    uint32_t value;
    char name[12];
};

typedef struct treenode Treenode;
struct treenode {
    int count; // number of keys in node
    Treeentry entry[MAX+1]; // 1-based k keys
    Treenode *branch[MAX+1]; // 0-based k-1 children/partitions of keys
};

bool SearchNode(Key target, Treenode *current, int *pos);
void InitNode(Treenode *root);
void ShowKeys(Treenode *node);

/* PushIn: inserts a key into a node
 * Pre:  medentry belongs at index pos in node *current, which has room for it
 * Post: Inserts key medentry and pointer medright into *current at index pos.
 * 
 */
void PushIn(Treeentry medentry, Treenode *medright, Treenode *current, int pos)
{
    int i;
    dprint("add %c\n", medentry.key);
    for (i = current->count; i > pos; i--) { // make a hole
        // shift all keys and branches to the right
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
}

/* Split: splits a full node
   Pre:  medentry belongs at index pos of node *current which is full
   Post: splits node *current with entry medentry and pointer medright at index pos
         into nodes *current and *newright with median entry newmedian.
   Uses: PushIn

 */
void Split(Treeentry medentry, Treenode *medright, Treenode *current, int pos,
        Treeentry *newmedian, Treenode **newright)
{
    dprint("split...count %d\n", current->count); // it is assumed that current is full
    int i;
    int median;
    if (pos <= MIN) median = MIN;
    else            median = MIN + 1;
    // get a new node and put it on the right
    *newright = (Treenode *) malloc(sizeof(Treenode));
    InitNode(*newright);
    for (i = median + 1; i <= MAX; i++) { // move half the keys
        (*newright)->entry[i - median] = current->entry[i];
        (*newright)->branch[i - median] = current->branch[i];
    }
    (*newright)->count = MAX - median;
    current->count = median;
    // see which side to add node to (right, or left)
    if (pos <= MIN) {
        printf("split...left %c\n", medentry.key); // it is assumed that current is full
        PushIn(medentry, medright, current, pos);
    } else {
        printf("split...right %c\n", medentry.key); // it is assumed that current is full
        PushIn(medentry, medright, *newright, pos - median);
    }
    *newmedian = current->entry[current->count];
    (*newright)->branch[0] = current->branch[current->count];
    current->count--;
}

/* SearchNode: searches keys in node for target.
 * Pre: target is a key and current points to a node of a B-tree
 * Post: Searches keys in node for target; returns location pos of target
 * or branch on which to continue.
 *
 */
bool SearchNode(Key target, Treenode *current, int *pos)
{
    printf("search node: %c\n", target);
    ShowKeys(current);
    if (target < current->entry[1].key) { // take left-most branch
        printf("go left\n");
        *pos = 0;
        return false;
    } else { // start sequential search through the keys
        printf("reverse linear search of %c - start at: %d - ", target, current->count);
        // terminate at pos=1 (1-based keys)
        for (*pos = current->count; target < current->entry[*pos].key && *pos > 1; (*pos)--) 
            ;
        dprint("linear search - end at [%d] = %d\n", *pos, current->entry[*pos].key);
        dprint("target: %d ?= entry: %d\n", target, current->entry[*pos].key);
        if (target == current->entry[*pos].key) {
            printf("key found\n");
        } else {
            printf("key not found\n");
        }
        return (target == current->entry[*pos].key);
    }
}

/* PushDown: recursively move down tree searching for newentry.
   Pre:  newentry belongs in the subtree to which current points.
   Post: newentry has been inserted into the subtree to which current points;
         if TRUE is returned, then the height of the subtree has grown, and
         medentry needs to be reinserted higher in the tree, with subtree
         medright on its right.
   Uses: PushDown recursively, SearchNode, Split, PushIn
    

 */
bool PushDown(Treeentry newentry, Treenode *current, Treeentry *medentry,
        Treenode **medright)
{
    int pos; // branch on which to continue the search
    dprint("push: %p\n", current);
    if (current == NULL) {
        dprint("final sorted insert: %c\n", newentry.key);
        *medentry = newentry;
        *medright = NULL;
        return true;
    } else { // search the current node
        if (SearchNode(newentry.key, current, &pos)) {
            dprint("warning inserting dup key into B-tree\n");
        }
        if (PushDown(newentry, current->branch[pos], medentry, medright)) {
            if (current->count < MAX) { // reinsert median key
                printf("add new key %c at %d\n", medentry->key, pos);
                PushIn(*medentry, *medright, current, pos); // add key to current node
                ShowKeys(current);
                return false;
            } else { // need to split the node
                printf("splitting at %d\n", pos);
                Split(*medentry, *medright, current, pos, medentry, medright);
                //printf("parent node: ");
                //ShowKeys(current);
                // note: medentry contains the new root key
                printf("left node: ");
                ShowKeys(current);
                printf("right node: ");
                ShowKeys(*medright);
                return true;
            }
        }
        dprint("fell through\n");
        return false; // superfluous?
    }
    return false;
}

Treenode *DeleteTree(Key target, Treenode *root)
{
    dprint("delete...\n");
    return NULL;
}


/* SearchTree: traverse B-tree looking for target.
   Pre:  The B-tree pointed to by root has been created.
   Post: If the key target is present in the B-tree, then the return
      value points to the node containing target in position 
      targetpos.  Otherwise, the return value is NULL and 
      targetpos is undefined.
   Uses: SearchTree recursively, SearchNode

 */
Treenode *SearchTree(Key target, Treenode *root, int *targetpos)
{
    dprint("search tree...\n");
    if (!root) return NULL;
    
    else if (SearchNode(target, root, targetpos)) return root;

    else return SearchTree(target, root->branch[*targetpos], targetpos);
}

/* InsertTree: inserts entry into the B-tree
   Pre:  The B-tree to which root points has been created, and no entry in
         the B-tree has key equal to newentry.key.
   Post: newentry has been inserted into the B-tree; the root is returned.
   Uses: PushDown

 */
Treenode *InsertTree(Treeentry newentry, Treenode *root)
{
    Treeentry medentry; // node to be reinserted as new root
    Treenode *medright; // subtree on right of medentry
    Treenode *newroot;  // used when the height of the tree increases

    //printf("insert: %c => %p\n", newentry.key, root);
    printf("insert: %c\n", newentry.key);
    if (PushDown(newentry, root, &medentry, &medright)) {
        // true - there is a key to be placed in a new root, 
        // and the height of the tree increases.
        newroot = (Treenode *) malloc(sizeof(Treenode));
        InitNode(newroot);
        newroot->count = 1;
        newroot->entry[1] = medentry; // key
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        printf("new root: %c\n", medentry.key);
        printf("\n");
        return newroot;
    }

    printf("\n");
    return root; // tree did not grow

}

/* InitNode: initialize a tree node
 *
 */
void InitNode(Treenode *root)
{
    int i;
    root->count = 0;
    for (i = 0; i < MAX+1; i++) {
        root->entry[i].key = DUMMY;
        root->branch[i] = NULL;
    }
}

void PrintRecord(Treeentry *entry)
{
    printf("key:   %c\n", entry->key);
    //printf("value: %d\n", entry->value);
    //printf("name:  %s\n", entry->name);
    printf("\n");
}

Treenode *visited[64];
uint8_t  ptr = 0;
bool NodeSeen(Treenode *root)
{
    int i;
    for (i = 0; i < ptr; i++) {
        if (visited[i] == root) return true;
    }
    visited[ptr++] = root;
    return false;
}

void ShowKeys(Treenode *node)
{
    int i;
    printf("keys: ");
    if (node->count == 0) {
        printf("none");
    } else {
        for (i = 1; i <= node->count; i++) {
            printf("%c - ", node->entry[i].key);
        }
    }
    printf("\n");
}

void ShowNodes(Treenode *root, int level)
{
    int i;
    if (root == NULL) return;
    //printf("ShowNodes: %d, level: %d\n", root->count, level);
    NodeSeen(root);
    //printf("Lvl:%d:%p]  ", level, root);
    printf("Lvl: [%d]  ", level);
    //for (i = 1; i <= root->count; i++) printf("%c - ", root->entry[i].key);
    for (i = 1; i <= root->count; i++) printf("%c - ", root->entry[i].key);
    printf("\n");
    for (i = 0; i < MAX; i++) {
        if (!NodeSeen(root->branch[i])) {
            ShowNodes(root->branch[i], level+1);
        }
   }
}

void test2()
{
    Treeentry e;
    int i;
    Treenode *root = (Treenode *) malloc(sizeof(Treenode));
    memset(root, 0, sizeof(Treenode));
    InitNode(root);

    //Key a[] = {1,3,5,7,2,4,6,8};
    //int len = sizeof(a) / sizeof(a[0]);
    //Key a[] = "abcdefghijklmnopqrstuvwxyz";
    Key a[] = "agfbkdhmjesirxclntup";
    int len = strlen(a);
    const char *names[] = {"bart", "cindy", "grant", "claire", "mackenzie", "taylor", "kevin", "alusia"};

    for (i = 0; i < len; i++) {
        e.key = a[i];
        //e.value = a[i] + i;
        //strcpy(e.name, names[i]);
        root = InsertTree(e, root);
    }
    ShowNodes(root, 0);
    //show_tree_bfs(root);
    return;

    int targetpos = 0;
    for (i = 0; i < len; i++) {
        targetpos = 0;
        Treenode *s = SearchTree(a[i], root, &targetpos);
        //if (s) printf("found [%d] => %c\n", targetpos, s->entry[targetpos].key);
        if (s) PrintRecord(&s->entry[targetpos]);
    }
}

void test1()
{
    Treeentry e;
    int i;
    Treenode *root = (Treenode *) malloc(sizeof(Treenode));
    memset(root, 0, sizeof(Treenode));
    InitNode(root);

    e.key = 42;
    strcpy(e.name, "bart");
    root = InsertTree(e, root);
 }

int main()
{
    test2();
}

