#ifndef _BTREE2_H_
#define _BTREE2_H_

#include <stdbool.h>

/* 
  Reference: CLRS3 - Chapter 18 - (499-502) 
 */

// A BTree node 
typedef struct BTreeNode 
{ 
    int *keys;  // An array of keys 
    int t;      // Minimum degree (defines the range for number of keys) 
    struct BTreeNode **C; // An array of child pointers 
    int n;     // Current number of keys 
    bool leaf; // Is true when node is leaf. Otherwise false 
  
} BTreeNode; 
  
typedef struct BTree 
{ 
    BTreeNode *root; // Pointer to root node 
    int t;  // Minimum degree 
} BTree; 


BTreeNode *BTreeNode_Constructor(int t, bool leaf);
void BTreeNode_Destructor(BTreeNode *node);
void BTreeNode_Remove(BTreeNode *node, int k);
void BTreeNode_RemoveFromLeaf(BTreeNode *node, int idx);
void BTreeNode_RemoveFromNonLeaf(BTreeNode *node, int idx);
void BTreeNode_Fill(BTreeNode *node, int idx);
void BTreeNode_Merge(BTreeNode *node, int idx);
void BTree_Insert(BTree *tree, int k);
void BTreeNode_InsertNonFull(BTreeNode *node, int k);
void BTreeNode_SplitChild(BTreeNode *node, int i, BTreeNode *y);
void BTreeNode_BorrowFromPrev(BTreeNode *node, int idx);
void BTreeNode_BorrowFromNext(BTreeNode *node, int idx);
int BTreeNode_FindKey(BTreeNode *node, int k);
int BTreeNode_GetPred(BTreeNode *node, int idx);
int BTreeNode_GetSucc(BTreeNode *node, int idx);
void BTreeNode_Traverse(BTreeNode *node);
BTreeNode *BTreeNode_Search(BTreeNode *node, int k);

  
void BTree_Traverse(BTree *tree);
BTreeNode* BTree_Search(BTree *tree, int k);
BTree *BTree_Constructor(int _t);
void BTree_Destructor(BTree *tree);


#endif // _BTREE2_H_
