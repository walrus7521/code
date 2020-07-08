#include <stdio.h>
#include <stdbool.h>

// set to larger value then needed
#define NMAX (16)
#define MAXCANDIDATES (NMAX)
bool finished = false;
void process_solution(int a[], int k, int input);
bool is_a_solution(int a[], int k, int n);
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates);

void backtrack(int a[], int k, int input)
{
    int c[MAXCANDIDATES];
    int ncandidates;
    if (is_a_solution(a, k, input)) {
        process_solution(a, k, input);
    } else {
        k++;
        construct_candidates(a, k, input, c, &ncandidates);
        for (int i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, input);
            if (finished) return;
        }
    }       
}

bool is_a_solution(int a[], int k, int n)
{
    return (k == n);
}

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i;
    bool in_perm[NMAX];
    
    for (i = 1; i < NMAX; i++) in_perm[i] = false;
    for (i = 0; i < k; i++) in_perm[ a[i] ] = true;

    *ncandidates = 0;
    for (i = 1; i <= n; i++) {
        if (in_perm[i] == false) {
            c[ *ncandidates ] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
}

void process_solution(int a[], int k, int input)
{
    for (int i = 1; i <= k; i++) printf(" %d", a[i]);
    printf("\n");
}

void generate_permutations(int n)
{
    int a[NMAX];
    backtrack(a, 0, n);
}

int main()
{
    generate_permutations(3);
}

