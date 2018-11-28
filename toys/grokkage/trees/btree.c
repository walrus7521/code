#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

#define MAX (4)
#define MIN (2)

typedef int Key;
typedef int Boolean;
enum { TRUE, FALSE };

typedef struct treeentry Treeentry;
struct treeentry {
    Key key;
    char name[4];
};

typedef struct treenode Treenode;
struct treenode {
    int count;
    Treeentry entry[MAX+1]; // 1-based
    Treenode *branch[MAX+1]; // 0-based
};

Boolean SearchNode(Key target, Treenode *current, int *pos);

void PushIn(Treeentry medentry, Treenode *medright, Treenode *current, int pos)
{
}

void Split(Treeentry medentry, Treenode *medright, Treenode *current, int pos,
        Treeentry *newmedian, Treenode **newright)
{
}

/* PushDown: recursively move down tree searching for newentry.
   Pre:  newentry belongs in the subtree to which current points.
   Post: newentry has been inserted into the subtree to which current points;
         if TRUE is returned, then the height of the subtree has grown, and
         medentry needs to be reinserted higher in the tree, with subtree
         medright on its right.
   Uses: PushDown recursively, SearchNode, Split, PushIn
    

 */
Boolean PushDown(Treeentry newentry, Treenode *current, Treeentry *medentry,
        Treenode **medright)
{
    int pos; // branch on which to continue the search
    if (current == NULL) {
        *medentry = newentry;
        *medright = NULL;
        return TRUE;
    } else { // search the current node
        if (SearchNode(newentry.key, current, &pos)) {
            printf("warning inserting dup key into B-tree\n");
        }
        if (PushDown(newentry, current->branch[pos], medentry, medright)) {
            if (current->count < MAX) { // reinsert median key
                PushIn(*medentry, *medright, current, pos); // add key to current node
                return FALSE;
            } else { // need to split the node
                Split(*medentry, *medright, current, pos, medentry, medright);
                return TRUE;
            }
        }
        return FALSE; // superfluous?
    }
    return FALSE;
}

Treenode *DeleteTree(Key target, Treenode *root)
{
    return NULL;
}

Boolean SearchNode(Key target, Treenode *current, int *pos)
{
    if (LT(target, current->entry[1].key)) {
        *pos = 0;
        return FALSE;
    } else {
        for (*pos = current->count; 
             LT(target, current->entry[*pos].key) && *pos > 1;
             (*pos)--) {
            ;
        }
        return EQ(target, current->entry[*pos].key);
    }
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

    if (PushDown(newentry, root, &medentry, &medright)) {

        // TRUE - there is a key to be placed in a new root, 
        // and the height of the tree increases.
        newroot = (Treenode *) malloc(sizeof(Treenode));
        newroot->count = 1;
        newroot->entry[1] = medentry; // key
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        return newroot;
    }

    return root; // tree did not grow

}

void init(Treenode *root)
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
    init(root);

    e.key = 42;
    strcpy(e.name, "bart");
    root = InsertTree(e, root);
  
}

