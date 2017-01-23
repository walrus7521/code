#include "pch.hpp"
#include "Sort.hpp"

using namespace std;

typedef std::array<int, 7> i7;

// arrange: B[0] < B[1] > B[3] < B[4] > B[5] ...
// 1: sort & interleave bottom and top halves
// 2: sort & swap pairs (A[1],A[2]), (A[3],A[4]),... 
// 3: no sort & rearrange elements around median, then interleave
// 4: no sort, no median, a mystery

void test_sort()
{
    i7 a{9, 4, 7, 3, 6, 2, 1};

    cout << "before" << endl;

    for (const auto& s: a)
        std::cout << s << ' ';
    cout << endl;

    std::sort(a.begin(), a.end());
    cout << "after" << endl;

    for (const auto& s: a)
        std::cout << s << ' ';
    cout << endl;

    for (int i = 0; i < a.size(); ++i) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }

}

int main()
{
    test_sort();
}

