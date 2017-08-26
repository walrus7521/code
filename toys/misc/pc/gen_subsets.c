/*
 * There are 2^n subsets of n things
 * a[] is the vector of each valid state:
 *      [111],[110],[101],...[000]
 *      each position in the vector is boolen: true or false
 *     and each valid state is a leaf of a full binary tree:
 *        
 *                             /----- root -----\
 *                           1/                 /\0
 *                           / \               /  \
 *                          /   \             /    \
 *                       11/     \10       01/      \00
 *                        /\     /\         /\      /\
 *                       /  \   /  \       /  \    /  \
 *                    111  110 101 100   011 010 001   000
 *
 *      Each boolean state is represented in the C vector: true/false.
 */

#include <stdio.h>
#include <stdlib.h>

#define dprintf printf
//#define dprintf(...)
#define MAXCANDIDATES 255
typedef int bool;
enum { FALSE=0, TRUE=1 };
bool finished = FALSE;

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    dprintf("construct_candidates...\n");
    c[0] = TRUE;
    c[1] = FALSE;
    *ncandidates = 2;
}

void process_solution(int a[], int k)
{
    int i;
    printf("{");
    for (i = 1; i <= k; i++)
        if (a[i] == TRUE) printf(" %d", i);
    printf(" }\n");
}

int is_a_solution(int a[], int k, int n)
{
    dprintf("is_a_solution(%d == %d) = %s...\n", k, n, (k==n) ? "true" : "false");
    return (k == n);
}

void backtrack(int a[], int k, int input)
{
    int c[MAXCANDIDATES], ncandidates, i;
    dprintf("backtrack(k=%d, in=%d)...a[", k, input);
    for (int i = 1; i <= k; ++i) dprintf("%d, ", a[i]);
    dprintf("]\n");
    if (is_a_solution(a, k, input))
        process_solution(a, k);
    else {
        k++;
        construct_candidates(a, k, input, c, &ncandidates);
        dprintf("process %d candidates\n", ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, input);
            dprintf("after call to backtrack for k = %d, i = %d\n", k, i);
            if (finished) return;
        }
    }
}

void generate_subsets(int n)
{
    int a[MAXCANDIDATES];
    backtrack(a, 0, n);
}

int main()
{
    generate_subsets(3);
    return 0;
}
