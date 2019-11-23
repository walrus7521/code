#include "utils2.h"

#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2
vi segment_tree;


void init_segment_tree(int N) {
    int length = (int)(2 * pow(2.0, floor((log((double)N)/log(2.0))+1)));
    segment_tree.resize(length, 0);
}

void build_segment_tree(int code, int A[], int node, int b, int e) {
    if (b == e) {
        if (code == RANGE_SUM) segment_tree[node] = A[b];
        else                   segment_tree[node] = b;
    } else {
        int leftIdx = 2 * node, rightIdx = 2 * node + 1;
        build_segment_tree(code, A, leftIdx, b, (b+e)/2);
        build_segment_tree(code, A, rightIdx, (b+e)/2+1, e);
        int lContent = segment_tree[leftIdx], rContent = segment_tree[rightIdx];

        if (code == RANGE_SUM) {
            segment_tree[node] = lContent+rContent;
        } else {
            int lValue = A[lContent], rValue = A[rContent];
            if (code == RANGE_MIN) 
                segment_tree[node] = (lValue <= rValue) ? lContent : rContent;
            else                   
                segment_tree[node] = (lValue >= rValue) ? lContent : rContent;
        }
    }
}

int query(int code, int A[], int node, int b, int e, int i, int j) {
    if (i > e || j < b) return -1; // interval doesn't intersect query interval
    if (b >= i && e <= j) return segment_tree[node]; // we're inside the interval
    // compute the minimum position in left and right part of interval
    int p1 = query(code, A, 2 * node, b, (b+e)/2, i, j);
    int p2 = query(code, A, 2 * node+1, (b+e)/2+1, e, i, j);

    if (p1 == -1) return p2;
    if (p2 == -1) return p1;

    if (code == RANGE_SUM) return p1 + p2;
    else if (code == RANGE_MIN) return (A[p1] <= A[p2]) ? p1 : p2;
    else                        return (A[p1] >= A[p2]) ? p1 : p2;
}

int main()
{
    int A[] = {8,7,3,9,5,1,10};
    init_segment_tree(7); 
    build_segment_tree(RANGE_MIN, A, 1, 0, 6); // start at node 1, not 0
    int rmq = query(RANGE_MIN, A, 1, 0, 6, 1, 3);
    printf("%d\n", rmq);
}


