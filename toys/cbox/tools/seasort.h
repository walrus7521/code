#ifndef _SEASORT_H_
#define _SEASORT_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h> // isspace
#include <stdlib.h>


#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exchg(A, B) { int t = A; A = B; B = t; } 

#define exchg2(X, Y) { \
    (X) = (X) ^ (Y);   \
    (Y) = (Y) ^ (X);   \
    (X) = (X) ^ (Y); }

#define cmpexchg(A, B) if (less(B, A)) exchg(A, B)


void sort_show(int a[], int n);
void read_quoted_string(char *s);
int split(char *line, char *words[]);
int boyer(char *haystack, char *needle, int start);
int match(char *string, char *pattern);
int palindrome(char *s);
int anagram(char *s1, int len1, char *s2, int len2);
int sequential_search(char *s, int n, char k);
int binsearch(char *s, int n, char k);
int find_first_k(int x, int v[], int n);
int partition(int *A, int lo, int hi);
void seasort_reverse(int a[], int n);
void quicksort(int *A, int lo, int hi);
void selection(int a[], int n);
void insertion(int a[], int n);
void bubble(int a[], int n);
void sort_interval(int a[], int sz, int start, int inc);
void shell(int a[], int sz);
void ss_merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
int *zipi(int a[], int b[], int len);
void zipr(int a[], int b[], int i, int len);
void test_zip();
void test_strings();
void test_sort();
int seasort_test();

#endif // _SEASORT_H_

