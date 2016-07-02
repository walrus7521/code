#include <iostream>
#include <queue>
#include <deque>

using std::cout;
using std::queue;
using std::deque;

typedef char Key, Value;

#define BRANCH_FACTOR 4
#define LT(a,b) ((a) < (b))
#define EQ(a,b) ((a) == (b))

enum {
    MAX_BRANCH = BRANCH_FACTOR,
    MIN_BRANCH = MAX_BRANCH/2,
    TRUE = 1,
    FALSE = 0,
};

typedef struct {
    Key key;
    Value value;
} pair;

typedef struct _btree_node {
    int count;
    pair entry[MAX_BRANCH+1];
    //pair[] entry = new pair[MAX_BRANCH+1];
    struct _btree_node *branch[MAX_BRANCH+1];
} btree_node;


class btree {
private:
    btree_node *root;
    btree_node *btree_search(Key target, btree_node *root, 
            int *intra_node_target_pos);
    int search_node(Key target, btree_node *current, int *pos);
    void btree_push_in(pair medentry, btree_node *medright, 
            btree_node *current, int pos);
    void btree_split(pair medentry, btree_node *medright, 
            btree_node *current, int pos, 
            pair *newmedian, btree_node **newright);
    int btree_push_down(pair newentry, btree_node *current, 
            pair *medentry, btree_node **medright);
public:
    btree();
    ~btree();
    bool btree_find(Key key);
    int btree_insert(pair entry);
    void btree_show();
};

btree::btree() 
{
    cout << "construct btree\n"; 
    root = (btree_node *) new btree_node;
    //root->entry = new pair[MAX_BRANCH+1];
    root->count = 0;
    for (int i = 0; i < MAX_BRANCH; i++) {
        root->branch[i] = NULL;
    }
}

btree::~btree() 
{    
    cout << "destroy btree\n"; 
    delete root;
    root = NULL;
}

void btree::btree_show()
{
    cout << "show btree\n"; 
    int counter = 1;
    int pos;
    char c;
    deque<btree_node*> q;
    btree_node *node, *tnode, *t;
    cout << "btree_show - enter root: " << root << "\n";
    if (!root) return;
    q.push_back(root);
    while (!q.empty()) {
        node = q.front();
        q.pop_front();
        for (pos = 0; pos < node->count+1; pos++) {
            c = node->entry[pos].key;
            if (isalpha(c)) {
                cout << " entry[" << pos << "]=" << node->entry[pos].key << "\n";
            }
            if (node->branch[pos] != NULL) {
                tnode = node->branch[pos];
                q.push_back(tnode);
                counter++;
            }
        }
    }
    cout << "num nodes " << counter << "\n";
}

btree_node *btree::btree_search(Key target, btree_node *root, int *intra_node_target_pos)
{
    cout << "btree_search - enter root: " << root << " - key " << target << "\n";
    if (!root) {
        return NULL;
    } else
    if (search_node(target, root, intra_node_target_pos)) {
        return root;
    } else {
        return btree_search(target, root->branch[*intra_node_target_pos], intra_node_target_pos);
    }
}

int btree::search_node(Key target, btree_node *current, int *pos)
{
    int found;
    if (LT(target, current->entry[1].key)) {
        *pos = 0;
        return FALSE;
    } else {
        for (*pos = current->count; 
                LT(target, current->entry[*pos].key) && *pos > 1; 
                (*pos)--) {
            ;
        }
        found = EQ(target, current->entry[*pos].key);
        cout << "found? " << found << " -> " << target << " : " << current->entry[*pos].key;
        return found;
    }
}

void btree::btree_push_in(pair medentry, btree_node *medright, btree_node *current, int pos)
{
    int i;
    for (i = current->count; i > pos; i--) {
        current->entry[i+1] = current->entry[i];
        current->branch[i+1] = current->branch[i];
    }
    current->entry[pos+1] = medentry;
    current->branch[pos+1] = medright;
    current->count++;
    cout << "push_in: count " << current->count << "\n";
}

void btree::btree_split(pair medentry, btree_node *medright, btree_node *current, int pos, 
            pair *newmedian, btree_node **newright)
{
    int i;
    int median;
    if (pos <= MIN_BRANCH) {
        median = MIN_BRANCH;
    } else {
        median = MIN_BRANCH+1;
    }
    *newright = (btree_node *) malloc(sizeof(btree_node));
    for (i = median+1; i <= MAX_BRANCH; i++) {
        (*newright)->entry[i-median] = current->entry[i];
        (*newright)->branch[i-median] = current->branch[i];
    }
    (*newright)->count = MAX_BRANCH - median;
    current->count = median;
    if (pos <= MIN_BRANCH) {
        btree_push_in(medentry, medright, current, pos);
    } else {
        btree_push_in(medentry, medright, *newright, pos-median);
    }
    *newmedian = current->entry[current->count];
    (*newright)->branch[0] = current->branch[current->count];
    current->count--;
}

int btree::btree_push_down(pair newentry, btree_node *current, pair *medentry,
            btree_node **medright)
{
    int pos;
    cout << "btree_push_down - ENTER\n";
    if (current == NULL) {
        *medentry = newentry;
        *medright = NULL;
        return TRUE;
    } else {
        if (search_node(newentry.key, current, &pos)) {
            cout << "warning: inserting duplicate key...\n";
        }
        if (btree_push_down(newentry, current->branch[pos],
                    medentry, medright)) {
            if (current->count < MAX_BRANCH) {
                btree_push_in(*medentry, *medright, current, pos);
                return FALSE;
            } else {
                btree_split(*medentry, *medright, current, pos,
                        medentry, medright);
                return TRUE;
            }
        }
        return FALSE;
    }
}

bool btree::btree_find(Key key)
{
    btree_node *find;
    int i;
    find = btree_search(key, root, &i);
    if (find) {
        cout << "found: " << find->entry[i].key << "\n";
    }
    return true;
}

int btree::btree_insert(pair newentry)
{
    pair medentry;
    btree_node *medright;
    btree_node *newroot;

    if (btree_push_down(newentry, root, &medentry, &medright)) {
        cout << "after return from btree_push_down..\n";
        newroot = (btree_node *) new btree_node;
        newroot->count = 1;
        newroot->entry[1] = medentry;
        newroot->branch[0] = root;
        newroot->branch[1] = medright;
        root = newroot;
    }
    /* else root remains unchanged */
    return 0;
}

int main(int args, char *argv[])
{
    btree bt;
    Key keys[] = {'a','g','o','y','f','b','w','k','d','h','m','v','j','e','s','i','r','x','c','z','q','l','n','t','u','p'};
    int num_keys;
    pair entry;
    num_keys = sizeof(keys) / sizeof(Key);
    for (int i = 0; i < num_keys; i++) {
        entry.key = keys[i];
        bt.btree_insert(entry);
    }
    bt.btree_show();
    return 0;
}

