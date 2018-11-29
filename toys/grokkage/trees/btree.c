#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

#define MAX (4)
#define MIN (2)

typedef int Key;

typedef struct treeentry Treeentry;
struct treeentry {
    Key key;
    char name[12];
};

typedef struct treenode Treenode;
struct treenode {
    int count;
    Treeentry entry[MAX+1]; // 1-based
    Treenode *branch[MAX+1]; // 0-based
};

bool SearchNode(Key target, Treenode *current, int *pos);
void InitNode(Treenode *root);

/* PushIn: inserts a key into a node
 * Pre:  medentry belongs at index pos in node *current, which has room for it
 * Post: Inserts key medentry and pointer medright into *current at index pos.
 * 
 */
void PushIn(Treeentry medentry, Treenode *medright, Treenode *current, int pos)
{
    int i;
    printf("push in...\n");
    for (i = current->count; i > pos; i--) { // make a hole
        // shift all keys and branches to the right
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
}

void Split(Treeentry medentry, Treenode *medright, Treenode *current, int pos,
        Treeentry *newmedian, Treenode **newright)
{
    printf("split...\n");
}

/* SearchNode: searches keys in node for target.
 * Pre: target is a key and current points to a node of a B-tree
 * Post: Searches keys in node for target; returns location pos of target
 * or branch on which to continue.
 *
 */
bool SearchNode(Key target, Treenode *current, int *pos)
{
    printf("search node: %d\n", target);
    if (target < current->entry[1].key) { // take left-most branch
        printf("go left\n");
        *pos = 0;
        return false;
    } else { // start sequential search through the keys
        printf("linear search - start at %d\n", current->count);
        for (*pos = current->count; target < current->entry[*pos].key && *pos > 1; (*pos)--) ;
        printf("linear search - end at [%d] = %d\n", *pos, current->entry[*pos].key);
        printf("target: %d ?= entry: %d\n", target, current->entry[*pos].key);
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
    printf("push: %p\n", current);
    if (current == NULL) {
        printf("null root\n");
        *medentry = newentry;
        *medright = NULL;
        return true;
    } else { // search the current node
        if (SearchNode(newentry.key, current, &pos)) {
            printf("warning inserting dup key into B-tree\n");
        }
        if (PushDown(newentry, current->branch[pos], medentry, medright)) {
            if (current->count < MAX) { // reinsert median key
                printf("pushing in at %d\n", pos);
                PushIn(*medentry, *medright, current, pos); // add key to current node
                return false;
            } else { // need to split the node
                printf("splitting at %d\n", pos);
                Split(*medentry, *medright, current, pos, medentry, medright);
                return true;
            }
        }
        printf("fell through\n");
        return false; // superfluous?
    }
    return false;
}

Treenode *DeleteTree(Key target, Treenode *root)
{
    printf("delete...\n");
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
    printf("search tree...\n");
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

    printf("insert: %d => %p\n", newentry.key, root);
    if (PushDown(newentry, root, &medentry, &medright)) {
        printf("grow in height\n");

        // true - there is a key to be placed in a new root, 
        // and the height of the tree increases.
        newroot = (Treenode *) malloc(sizeof(Treenode));
        InitNode(newroot);
        newroot->count = 1;
        newroot->entry[1] = medentry; // key
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        return newroot;
    }

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
        root->entry[i].key = -1;
        root->branch[i] = NULL;
    }
}

int main()
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

