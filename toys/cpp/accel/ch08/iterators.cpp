#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/* sequential read-only access: input iterator
 * ==, !=, ++ pre/post, and * (dereference), and -> & (*).
 */
template <class In, class X>
In find(In begin, In end, X& x)
{
    while (begin != end && *begin != x)
        ++begin;
    return begin;
}

/* sequential write-only access: output iterator
 * ==, !=, ++ pre/post, and * (dereference), and -> & (*).
 * and *it = x (assignment), and back_inserter
 */
template <class In, class Out>
Out copy(In begin, In end, Out dest)
{
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

/* sequential read-write access: forward iterator
 * ==, !=, ++ pre/post, and * (dereference), and -> & (*).
 * and *it = x (assignment), and back_inserter
 */
template <class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
    while (beg != end) {
        if (*beg == x)
            *beg = y;
        ++beg;
    }
}

/* reversible access: bidirectional iterator
 * ==, !=, ++ pre/post, and * (dereference), and -> & (*).
 * and *it = x (assignment), and back_inserter
 * and -- (pre/post)
 */
template <class Bi>
void reverse(Bi beg, Bi end)
{
    while (beg != end) {
        -- end;
        if (beg != end)
            swap(*beg++, *end);
    }
}

/* random-access iterator
 * ==, !=, ++ pre/post, and * (dereference), and -> & (*).
 * and *it = x (assignment), and back_inserter
 * and -- (pre/post)
 * and p+n, p-n, n+p
 * p[n] (same as *(p+n)
 * p<q. p>q, p<=q,p>=q
 */
template <class Ran, class X>
bool binary_search(Ran beg, Ran end, const X& x)
{
    while (beg < end) {
        Ran mid = beg + (end - beg) / 2;
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            beg = mid + 1;
        else return true;
    }
    return false;
}
int main()
{
    int tmp[] = {1, 2, 3, 4};
    vector<int> vi(tmp, tmp+3);
    vector<int>::const_iterator it;
    int x = 7;
    cout << "find " << x << endl;
    it = find(vi.begin(), vi.end(), x);
    if (it != vi.end()) {
        cout << "found " << *it << endl;
    } else {
        cout << "not found\n";
    }
    return 0;
}
