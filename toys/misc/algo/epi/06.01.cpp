#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::cout;
using std::endl;
using std::vector;
using std::swap;

void myswap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void DutchFlagPartition2(int pivot_index, int *A, int len) {
    int pivot = A[pivot_index];

    printf("pivot = %d\n", pivot);
    /**
      * keep the following invariants during partitioning:
      * bottom group: A_ref[0 : smaller - 1].
      * middle group: A_ref[smaller : equal - 1].
      * unclassified group: A_ref[equal : larger].
      * top group: A_ref[larger + 1 : A-ref.size() - 1].
      */

    int smaller = 0, equal = 0, larger = len - 1;
    // when there is any unclassified element.
    while (equal <= larger) {
        // A_ref[equal] is the incoming unclassified element.
        if (A[equal] < pivot) {
            myswap(A, smaller++, equal++);
        } else
        if (A[equal] == pivot) {
            ++equal;
        } else { // A_ref[equal] > pivot.
            myswap(A, equal, larger--);
        }
    }
}

void DutchFlagPartition1(int pivot_index, vector<int>* A) {
    auto& A_ref = *A;
    int pivot = A_ref[pivot_index];

    cout << "pivot = " << pivot << endl;
    /**
      * keep the following invariants during partitioning:
      * bottom group: A_ref[0 : smaller - 1].
      * middle group: A_ref[smaller : equal - 1].
      * unclassified group: A_ref[equal : larger].
      * top group: A_ref[larger + 1 : A-ref.size() - 1].
      */

    int smaller = 0, equal = 0, larger = A_ref.size() - 1;
    // when there is any unclassified element.
    while (equal <= larger) {
        // A_ref[equal] is the incoming unclassified element.
        if (A_ref[equal] < pivot) {
            swap(A_ref[smaller++], A_ref[equal++]);
        } else
        if (A_ref[equal] == pivot) {
            ++equal;
        } else { // A_ref[equal] > pivot.
            swap(A_ref[equal], A_ref[larger--]);
        }
    }
}

/* still need to implement variants
 */
void dump2(int *vi, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%d\n", vi[i]);
    }
    printf("\n");
}

void dump1(vector<int>& vi)
{
    for (vector<int>::const_iterator vit = vi.begin(); vit != vi.end(); ++vit) {
        cout << *vit << endl;
    }
    cout << endl << endl;
}

void test1()
{
    vector<int> vi = {3, 1, 0, 8, 6, 7, 5, 3, 0, 9};
    dump1(vi);
    DutchFlagPartition1(7, &vi);
    dump1(vi);
}

void test2()
{
    int vi[] = {3, 1, 0, 8, 6, 7, 5, 3, 0, 9};
    dump2(vi, 10);
    DutchFlagPartition2(7, vi, 10);
    dump2(vi, 10);
}

int main()
{
    test1();
    //test2();
    return 0;
}
