#include <iostream> 
#include <array>
#include <vector>

using namespace std;


/*  The Dutch national flag problem
 *
 *  Write a function that takes an array A of length n and an index i into 
 *  A, and rearranges the elements such that all elements less than A[i] appear
 *  first, followed by elements equal to A[i], followed by elements greater
 *  than A[i].
 *
 */

using namespace std;

void myswap(vector<int> a, int i, int j)
{
    cout << "swap: " << i << ", " << j << endl;
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

/* i is the pivot
 */
void dutch(vector<int>& a, int i)
{
    int m = a[i], n = a.size();
    if (i == 0 || i == n-1) return;
    a[0] = m;
    /* perk it down */
    for (int j= 2; j < n; ++j) {
        cout << "i: " << a[j] << "j: " << a[j-1] << endl;
        if (a[j] < a[j-1]) myswap(a, j, j-1);
    }
}

void show(const vector<int>& a)
{
    for(const auto& s: a)
        cout << s << ' ';
    cout << endl;
}

int main()
{
    vector<int> a{ 0, 8, 2, 3, 5, 9, 1};
    dutch(a, 1);
    show(a);
}
