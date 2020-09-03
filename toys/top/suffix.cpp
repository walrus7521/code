#include "util.h"

char S[1001];
int SA[1001], n;
int SA_cmp(const void *a, const void *b) { return strcmp(S + *(int*)a, S + *(int*)b); }

void suffix(const char *s)
{
    //n = strlen(gets(S));
    strncpy(S, s, strlen(s));
    n = strlen(S);
    printf("n: %d %s\n", n, S);
    for (int i = 0; i < n; i++) SA[i] = i; // sort
    qsort(SA, n, sizeof(int), SA_cmp);
    for (int i = 0; i < n; i++) printf("%d %s\n", SA[i], S+SA[i]);
}

int main()
{
    const char *str = "acacag$";
    suffix(str);
    printf("\n");
}

