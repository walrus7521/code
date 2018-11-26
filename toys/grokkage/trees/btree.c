#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

#define MAX 4
#define MIN 2

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

Boolean PushDown(Treeentry newentry, Treenode *current, Treeentry *medentry,
        Treenode **medright)
{
    return FALSE;
}

void PushIn(Treeentry medentry, Treenode *medright, Treenode *current, int pos)
{
}

void Split(Treeentry medentry, Treenode *medright, Treenode *current, int pos,
        Treeentry *newmedian, Treenode **newright)
{
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

Treenode *SearchTree(Key target, Treenode *root, int *targetpos)
{
    if (!root) return NULL;
    
    else if (SearchNode(target, root, targetpos)) return root;

    else return SearchTree(target, root->branch[*targetpos], targetpos);
}

Treenode *InsertTree(Treeentry newentry, Treenode *root)
{
    return NULL;
}

int main()
{
}

