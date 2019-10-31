#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "btree2.h"

/* 
  Reference: CLRS3 - Chapter 18 - (499-502) 
 */

BTreeNode *BTreeNode_Constructor(int t, bool leaf) 
{ 
    BTreeNode *bn = (BTreeNode *) malloc(sizeof(BTreeNode));
    bn->leaf = leaf;
    bn->n = 0;
    bn->t = t;
    bn->keys = (int *) malloc(sizeof(int) * t);
    bn->C = (BTreeNode **) malloc(sizeof(BTreeNode *) * t);
    return bn;
} 
  
void BTreeNode_Destructor(BTreeNode *node)
{
    free(node);
    node = NULL;
}

// A utility function that returns the index of the first key that is 
// greater than or equal to k 
int BTreeNode_FindKey(BTreeNode *node, int k) 
{ 
    int idx=0; 
    while (idx < node->n && node->keys[idx] < k) {
        ++idx; 
    }
    return idx; 
} 
  
// A function to remove the key k from the sub-tree rooted with this node 
void BTreeNode_Remove(BTreeNode *node, int k) 
{ 
    int idx = BTreeNode_FindKey(node, k); 
  
    // The key to be removed is present in this node 
    if (idx < node->n && node->keys[idx] == k) { 
        // If the node is a leaf node - removeFromLeaf is called 
        // Otherwise, removeFromNonLeaf function is called 
        if (node->leaf) 
            BTreeNode_RemoveFromLeaf(node, idx);
        else
            BTreeNode_RemoveFromNonLeaf(node, idx); 
    } else { 
        // If this node is a leaf node, then the key is not present in tree 
        if (node->leaf) 
        { 
            printf("The key %d is does not exist in the tree\n", k); 
            return; 
        } 
  
        // The key to be removed is present in the sub-tree rooted with this node 
        // The flag indicates whether the key is present in the sub-tree rooted 
        // with the last child of this node 
        bool flag = ( (idx == node->n)? true : false ); 
  
        // If the child where the key is supposed to exist has less that t keys, 
        // we fill that child 
        if (node->C[idx]->n < node->t) 
            BTreeNode_Fill(node, idx); 
  
        // If the last child has been merged, it must have merged with the previous 
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the 
        // (idx)th child which now has atleast t keys 
        if (flag && idx > node->n) 
            BTreeNode_Remove(node->C[idx-1], k); 
        else
            BTreeNode_Remove(node->C[idx], k);
    } 
    return; 
} 
  
// A function to remove the idx-th key from this node - which is a leaf node 
void BTreeNode_RemoveFromLeaf(BTreeNode *node, int idx) 
{ 
    int i;
    // Move all the keys after the idx-th pos one place backward 
    for (i = idx+1; i < node->n; ++i) 
        node->keys[i-1] = node->keys[i]; 
  
    // Reduce the count of keys 
    node->n--; 
  
    return; 
} 
  
// A function to remove the idx-th key from this node - which is a non-leaf node 
void BTreeNode_RemoveFromNonLeaf(BTreeNode *node, int idx) 
{ 
  
    int k = node->keys[idx]; 
  
    // If the child that precedes k (C[idx]) has atleast t keys, 
    // find the predecessor 'pred' of k in the subtree rooted at 
    // C[idx]. Replace k by pred. Recursively delete pred 
    // in C[idx] 
    if (node->C[idx]->n >= node->t) 
    { 
        int pred = BTreeNode_GetPred(node, idx); 
        node->keys[idx] = pred; 
        BTreeNode_Remove(node->C[idx], pred); 
    } 
  
    // If the child C[idx] has less that t keys, examine C[idx+1]. 
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
    // the subtree rooted at C[idx+1] 
    // Replace k by succ 
    // Recursively delete succ in C[idx+1] 
    else if  (node->C[idx+1]->n >= node->t) 
    { 
        int succ = BTreeNode_GetSucc(node, idx); 
        node->keys[idx] = succ; 
        BTreeNode_Remove(node->C[idx+1], succ); 
    } 
  
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
    // into C[idx] 
    // Now C[idx] contains 2t-1 keys 
    // Free C[idx+1] and recursively delete k from C[idx] 
    else
    { 
        BTreeNode_Merge(node, idx); 
        BTreeNode_Remove(node->C[idx], k); 
    } 
    return; 
} 
  
// A function to get predecessor of keys[idx] 
int BTreeNode_GetPred(BTreeNode *node, int idx) 
{ 
    // Keep moving to the right most node until we reach a leaf 
    BTreeNode *cur = node->C[idx]; 
    while (!cur->leaf) 
        cur = cur->C[cur->n]; 
  
    // Return the last key of the leaf 
    return cur->keys[cur->n-1]; 
} 
  
int BTreeNode_GetSucc(BTreeNode *node, int idx) 
{ 
  
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf 
    BTreeNode *cur = node->C[idx+1]; 
    while (!cur->leaf) 
        cur = cur->C[0]; 
  
    // Return the first key of the leaf 
    return cur->keys[0]; 
} 
  
// A function to fill child C[idx] which has less than t-1 keys 
void BTreeNode_Fill(BTreeNode *node, int idx) 
{ 
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
    // from that child 
    if (idx!=0 && node->C[idx-1]->n >= node->t) 
        BTreeNode_BorrowFromPrev(node, idx); 
  
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
    // from that child 
    else if (idx != node->n && node->C[idx+1]->n >= node->t) 
        BTreeNode_BorrowFromNext(node, idx); 
  
    // Merge C[idx] with its sibling 
    // If C[idx] is the last child, merge it with with its previous sibling 
    // Otherwise merge it with its next sibling 
    else
    { 
        if (idx != node->n) 
            BTreeNode_Merge(node, idx); 
        else
            BTreeNode_Merge(node, idx-1); 
    } 
    return; 
} 
  
// A function to borrow a key from C[idx-1] and insert it 
// into C[idx] 
void BTreeNode_BorrowFromPrev(BTreeNode *node, int idx) 
{ 
    BTreeNode *child = node->C[idx]; 
    BTreeNode *sibling = node->C[idx-1]; 
  
    // The last key from C[idx-1] goes up to the parent and key[idx-1] 
    // from parent is inserted as the first key in C[idx]. Thus, the  loses 
    // sibling one key and child gains one key 
  
    int i;
    // Moving all key in C[idx] one step ahead 
    for (i = child->n-1; i >= 0; --i) 
        child->keys[i+1] = child->keys[i]; 
  
    // If C[idx] is not a leaf, move all its child pointers one step ahead 
    if (!child->leaf) 
    { 
        for (i = child->n; i>=0; --i) 
            child->C[i+1] = child->C[i]; 
    } 
  
    // Setting child's first key equal to keys[idx-1] from the current node 
    child->keys[0] = node->keys[idx-1]; 
  
    // Moving sibling's last child as C[idx]'s first child 
    if(!child->leaf) 
        child->C[0] = sibling->C[sibling->n]; 
  
    // Moving the key from the sibling to the parent 
    // This reduces the number of keys in the sibling 
    node->keys[idx-1] = sibling->keys[sibling->n-1]; 
  
    child->n += 1; 
    sibling->n -= 1; 
  
    return; 
} 
  
// A function to borrow a key from the C[idx+1] and place 
// it in C[idx] 
void BTreeNode_BorrowFromNext(BTreeNode *node, int idx) 
{ 
    BTreeNode *child = node->C[idx]; 
    BTreeNode *sibling = node->C[idx+1]; 
  
    // keys[idx] is inserted as the last key in C[idx] 
    child->keys[(child->n)] = node->keys[idx]; 
  
    // Sibling's first child is inserted as the last child 
    // into C[idx] 
    if (!(child->leaf)) 
        child->C[(child->n)+1] = sibling->C[0]; 
  
    //The first key from sibling is inserted into keys[idx] 
    node->keys[idx] = sibling->keys[0]; 
  
    int i;
    // Moving all keys in sibling one step behind 
    for (i = 1; i < sibling->n; ++i) 
        sibling->keys[i-1] = sibling->keys[i]; 
  
    // Moving the child pointers one step behind 
    if (!sibling->leaf) { 
        for(i = 1; i <= sibling->n; ++i) 
            sibling->C[i-1] = sibling->C[i]; 
    } 
  
    // Increasing and decreasing the key count of C[idx] and C[idx+1] 
    // respectively 
    child->n += 1; 
    sibling->n -= 1; 
  
    return; 
} 
  
// A function to merge C[idx] with C[idx+1] 
// C[idx+1] is freed after merging 
void BTreeNode_Merge(BTreeNode *node, int idx) 
{ 
    BTreeNode *child = node->C[idx]; 
    BTreeNode *sibling = node->C[idx+1]; 
  
    // Pulling a key from the current node and inserting it into (t-1)th 
    // position of C[idx] 
    child->keys[node->t-1] = node->keys[idx]; 
  
    int i;
    // Copying the keys from C[idx+1] to C[idx] at the end 
    for (i = 0; i < sibling->n; ++i) 
        child->keys[i+node->t] = sibling->keys[i]; 
  
    // Copying the child pointers from C[idx+1] to C[idx] 
    if (!child->leaf) 
    { 
        for(i = 0; i <= sibling->n; ++i) 
            child->C[i+node->t] = sibling->C[i]; 
    } 
  
    // Moving all keys after idx in the current node one step before - 
    // to fill the gap created by moving keys[idx] to C[idx] 
    for (i = idx+1; i < node->n; ++i) 
        node->keys[i-1] = node->keys[i]; 
  
    // Moving the child pointers after (idx+1) in the current node one 
    // step before 
    for (i = idx+2; i <= node->n; ++i) 
        node->C[i-1] = node->C[i]; 
  
    // Updating the key count of child and the current node 
    child->n += sibling->n+1; 
    node->n--; 
  
    // Freeing the memory occupied by sibling 
    BTreeNode_Destructor(sibling);
    return; 
} 
  
// The main function that inserts a new key in this B-Tree 
void BTree_Insert(BTree *tree, int k) 
{ 
    // If tree is empty 
    if (tree->root == NULL) 
    { 
        // Allocate memory for root 
        tree->root = BTreeNode_Constructor(tree->t, true);
        tree->root->keys[0] = k;  // Insert key 
        tree->root->n = 1;  // Update number of keys in root 
    } 
    else // If tree is not empty 
    { 
        // If root is full, then tree grows in height 
        if (tree->root->n == 2*tree->t-1) 
        { 
            // Allocate memory for new root 
            BTreeNode *s = BTreeNode_Constructor(tree->t, true);
  
            // Make old root as child of new root 
            s->C[0] = tree->root; 
  
            // Split the old root and move 1 key to the new root 
            BTreeNode_SplitChild(s, 0, tree->root); 
  
            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0; 
            if (s->keys[0] < k) 
                i++; 
            BTreeNode_InsertNonFull(s->C[i], k); 
  
            // Change root 
            tree->root = s; 
        } 
        else  // If root is not full, call insertNonFull for root 
            BTreeNode_InsertNonFull(tree->root, k); 
    } 
} 
  
// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
void BTreeNode_InsertNonFull(BTreeNode *node, int k) 
{ 
    // Initialize index as index of rightmost element 
    int i = node->n-1; 
  
    // If this is a leaf node 
    if (node->leaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && node->keys[i] > k) 
        { 
            node->keys[i+1] = node->keys[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        node->keys[i+1] = k; 
        node->n = node->n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && node->keys[i] > k) 
            i--; 
  
        // See if the found child is full 
        if (node->C[i+1]->n == 2*node->t-1) 
        { 
            // If the child is full, then split it 
            BTreeNode_SplitChild(node, i+1, node->C[i+1]); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (node->keys[i+1] < k) 
                i++; 
        } 
        BTreeNode_InsertNonFull(node->C[i+1], k); 
    }
} 
  
// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void BTreeNode_SplitChild(BTreeNode *node, int i, BTreeNode *y) 
{ 
   // Create a new node which is going to store (t-1) keys 
    // of y 
    BTreeNode *z = BTreeNode_Constructor(y->t, y->leaf); 
    z->n = node->t - 1; 

    int j;  
    // Copy the last (t-1) keys of y to z 
    for (j = 0; j < node->t-1; j++) 
        z->keys[j] = y->keys[j+node->t]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (j = 0; j < node->t; j++) 
            z->C[j] = y->C[j + node->t]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = node->t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (j = node->n; j >= i+1; j--) 
        node->C[j+1] = node->C[j]; 
  
    // Link the new child to this node 
    node->C[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (j = node->n-1; j >= i; j--) 
        node->keys[j+1] = node->keys[j]; 
  
    // Copy the middle key of y to this node 
    node->keys[i] = y->keys[node->t-1]; 
  
    // Increment count of keys in this node 
    node->n++;
} 
  
// Function to traverse all nodes in a subtree rooted with this node 
void BTreeNode_Traverse(BTreeNode *node) 
{ 
    // There are n keys and n+1 children, travers through n keys 
    // and first n children 
    int i; 
    for (i = 0; i < node->n; i++) 
    { 
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted with child C[i]. 
        if (node->leaf == false) 
            BTreeNode_Traverse(node->C[i]); 
        printf(" ", node->keys[i]);
    } 
  
    // Print the subtree rooted with last child 
    if (node->leaf == false) 
        BTreeNode_Traverse(node->C[i]);
} 
  
// Function to search key k in subtree rooted with this node 
BTreeNode *BTreeNode_Search(BTreeNode *node, int k) 
{ 
    // Find the first key greater than or equal to k 
    int i = 0; 
    while (i < node->n && k > node->keys[i]) 
        i++; 
  
    // If the found key is equal to k, return this node 
    if (node->keys[i] == k) 
        return node; 
  
    // If key is not found here and this is a leaf node 
    if (node->leaf == true) 
        return NULL; 
  
    // Go to the appropriate child 
    return BTreeNode_Search(node->C[i], k); 
}


void BTree_Remove(BTree *tree, int k) 
{ 
    if (!tree->root) 
    { 
        printf("The tree is empty\n");
        return; 
    } 
  
    // Call the remove function for root 
    BTreeNode_Remove(tree->root, k); 
  
    // If the root node has 0 keys, make its first child as the new root 
    //  if it has a child, otherwise set root as NULL 
    if (tree->root->n==0) 
    { 
        BTreeNode *tmp = tree->root;
        if (tree->root->leaf) 
            tree->root = NULL; 
        else
            tree->root = tree->root->C[0]; 
  
        // Free the old root 
        BTreeNode_Destructor(tmp);
    } 
    return; 
} 
  
void BTree_Traverse(BTree *tree) 
{ 
    //if (root != NULL) root->traverse(); 
} 
  
// function to search a key in this tree 
BTreeNode* BTree_Search(BTree *tree, int k) 
{ 
    return (tree->root == NULL)? NULL : BTreeNode_Search(tree->root, k);
} 

BTree *BTree_Constructor(int _t)
{
    BTree *bt = (BTree *) malloc(sizeof(BTree));
    bt->t = _t;
    return bt;
}

void BTree_Destructor(BTree *tree)
{
    free(tree);
    tree = NULL;
}

