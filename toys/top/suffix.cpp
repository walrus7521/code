#include "util.h"

char S[1001];
int SuffixArray[1001]; // suffix array
int SA_cmp(const void *a, const void *b) { return strcmp(S + *(int*)a, S + *(int*)b); }
void suffix(const char *s, int n)
{
    strncpy(S, s, n);
    for (int i = 0; i < n; i++) SuffixArray[i] = i; // sort
    qsort(SuffixArray, n, sizeof(int), SA_cmp);
    for (int i = 0; i < n; i++) printf("%d %s\n", SuffixArray[i], S+SuffixArray[i]);
}

void search(const char *pat, int m, const char *txt, int n)
{
    // Do simple binary search for the pat in txt using the built suffix array 
    int l = 0, r = n-1;  // Initilize left and right indexes 
    while (l <= r) { 
        // See if 'pat' is prefix of middle suffix in suffix array 
        int mid = l + (r - l)/2; 
        printf("comparing: %s and %s at %d\n", pat, txt+SuffixArray[mid], mid);
        int result = strncmp(pat, txt+SuffixArray[mid], m); 
        if (result == 0) { // match found? first occurrence
            printf("Pattern found at index: %d\n", SuffixArray[mid]);
            return; 
        } 
        if (result < 0) r = mid - 1; // move left, patt is lexicog less than mid suffix
        else l = mid + 1; // Otherwise move to right half 
    } 
    printf("Pattern not found\n");
}

int main()
{
    const char *txt = "acacag$";
    const char *pat = "cac";
    int n = strlen(txt);

    printf("text: %s, n: %d\n", txt, n);

    suffix(txt, n);

    int m = strlen(pat); 
    // search pat in txt using the built suffix array 
    search(pat, m, txt, n);

    printf("\n");
}

