#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::swap;

void DutchFlagPartition(int pivot_index, vector<int>* A) {
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

void dump(vector<int>& vi)
{
    for (vector<int>::const_iterator vit = vi.begin(); vit != vi.end(); ++vit) {
        cout << *vit << endl;
    }
    cout << endl << endl;
}

int main()
{
    vector<int> vi = {3, 1, 0, 8, 6, 7, 5, 3, 0, 9};
    dump(vi);
    DutchFlagPartition(7, &vi);
    dump(vi);
    return 0;
}
