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
    return true;
}

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    *ncandidates = 1;
    a[0] = 1;
}

void process_solution(int a[], int k, int input)
{
    printf("done\n");
}

void queens(int n)
{
    int a[NMAX];
    backtrack(a, 0, n);
}

int main()
{
    queens(8);
}

