#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAXCANDIDATES 255

typedef int bool;
enum { FALSE=0, TRUE=1 };

bool finished = FALSE;
int solution_count = 0;

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i, j;
    bool legal_move;

    dbg_log(1, "construct_candidates - enter k %d, n %d\n", k, n);
    *ncandidates = 0;
    for (i = 1; i <= n; i++) {
        legal_move = TRUE;
        for (j = 1; j < k; j++) {
            if (abs((k)-j) == abs(i-a[j]))
                legal_move = FALSE;
            if (i == a[j])
                    legal_move = FALSE;
        }
        if (legal_move == TRUE) {
            c[*ncandidates] = i;
            *ncandidates= *ncandidates + 1;
            dbg_log(1, "found a legal move %d ncandidates %d\n", i, *ncandidates);
        }
    }
}

void process_solution(int a[], int k)
{
    int i;
    solution_count++;
    dbg_log(1, "process_solution - enter k %d\n", k);
}

int is_a_solution(int a[], int k, int n)
{
    dbg_log(1, "is_a_solution - enter k %d, n %d\n", k, n);
    return (k == n);
}

void backtrack(int a[], int k, int input)
{
    int c[MAXCANDIDATES];
    int ncandidates;
    int i;

    dbg_log(1, "backtrack - enter k %d\n", k);
    if (is_a_solution(a, k, input))
        process_solution(a, k);
    else {
        k++;
        construct_candidates(a, k, input, c, &ncandidates);
        dbg_log(1, "process %d candidates\n", ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, input);
            if (finished) return;
        }
    }
}

void nqueens(int n)
{
    int a[MAXCANDIDATES];
    solution_count = 0;
    backtrack(a, 0, n);
    printf("n = %d solution_count = %d\n", n, solution_count);
}

int main()
{
    int i;
    for (i = 1; i <= 8; i++)
        nqueens(i);
    return 0;
}
