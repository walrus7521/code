#include <stdio.h>
#include <stdlib.h>

#define dprintf printf
//#define dprintf(...)
#define NMAX 255
typedef int bool;
enum { FALSE=0, TRUE=1 };
bool finished = FALSE;

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i;
    bool in_perm[NMAX];
    for (i = 1; i < NMAX; i++) in_perm[i] = FALSE;
    for (i = 0; i < k; i++) in_perm[ a[i] ] = TRUE;
    *ncandidates = 0;
    for (i = 1; i <= n; i++) {
        if (in_perm[i] == FALSE) {
            c[ *ncandidates ] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
    dprintf("      -> %d candidates -> [k=%d]: c[", *ncandidates, k);
    for (i = 0; i < *ncandidates; ++i) {
        dprintf("%d, ", c[i]);
    }
    printf("]\n");
}

void process_solution(int a[], int k)
{
    int i;
    dprintf("**** solution[k=%d] => ", k);
    printf("{");
    for (i = 1; i <= k; i++) printf(" %d", a[i]);
    printf("}\n");
}

int is_a_solution(int a[], int k, int n)
{
    return (k == n);
}

void backtrack(int a[], int k, int n)
{
    int c[NMAX];
    int ncandidates = 0;
    int i;
    dprintf("    backtrack[k=%d]...a[", k);
    for (int i = 1; i <= k; ++i) dprintf("%d, ", a[i]);
    dprintf("]\n");
    if (is_a_solution(a, k, n))
        process_solution(a, k);
    else {
        k++;
        construct_candidates(a, k, n, c, &ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, n);
            if (finished) return;
        }
    }
}

void generate_permutations(int n)
{
    int a[NMAX];
    dprintf("generate_permutations[n=%d]\n", n);
    backtrack(a, 0, n);
}

int main()
{
    generate_permutations(3);
}
