#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;


int main()
{
    int order[] = {1, 2, 3};
    int n = 3;
    do {
        for (int i = 0; i < n; i++) {
            printf(" %d", order[i]);
        }
        printf("\n");
    } while (next_permutation(order, order+n));
}


