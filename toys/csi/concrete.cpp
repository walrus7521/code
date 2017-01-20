#include <cstdio>
#include <iostream>
#include <algorithm>

/*
 * problems: smallest change that can be made, hanoi,
 * levenshtein distance, maximum trappable water.
 *
 */

using namespace std;

/*
 * max first element is 1. 2nd element is 2, and 2 is less
 * than or equal to 1 + 1, so we can produce all values up
 * to and including 3 now. 3rd element is 2, which allows
 * us to produce values up to and including 5. 4th element
 * is 4, which allows us to produce all values up to 9. 5th
 * element is 12, which is greater than 9 + 1, so we cannot
 * produce 10, so we stop.  10 is the smallest number that
 * cannot be produced.
 *
 */
int max_subset_sum(int sorted[], int len)
{
    for (size_t i = 0; i < len; ++i) {
        printf("max[%zu] = %d\n", i, sorted[i]);
    }
    return 0;
}

void show(int a[], size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a[] = {12,2,1,15,2,4};
    size_t len = sizeof(a) / sizeof(a[0]);

    show(a, len);
    std::sort(a, a+len);
    max_subset_sum(a, len);
    show(a, len);
}
