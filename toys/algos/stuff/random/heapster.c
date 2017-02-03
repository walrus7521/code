#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int max;
    int nelems;
    int *A;
} heap;

heap *create(int size)
{
    heap *h = malloc(sizeof(heap));
    h->A = malloc(sizeof(int) * size);
    h->max = size;
    h->nelems = 0;
    return h;
}

void swap(heap *h, int x, int y)
{
    int tmp;
    tmp = h->A[x];
    h->A[x] = h->A[y];
    h->A[y] = tmp;
}

void perc_up(heap *h, int k, int x)
{
    while (k > 1 && x > h->A[k/2]) {
        h->A[k] = h->A[k/2];
        k /= 2;
    }
    h->A[k] = x;
}

void perc_down(heap *h, int k)
{
/*
perc_down(r, n)
  r = subscript of the root of subtree where the process will begin
  c = subscript of the left child
  n = number of elements in the entire array
  
  c = 2 * r   // add + 1 if the heap is stored using 0 based subscripts
  
  while (c < n)
    if (c < n-1 AND array[c] < array[c+1])
      increment c by 1
    endif
    
    if array[r] < array[c]
      swap array[r] and array[c]
      r = c
      c = 2 * c
    else
      break out of loop
    endif
    increment c by 1
  endwhile
*/    
    int c;
    c = 2 * k;
      
    while (c < h->nelems) {
        if (c < h->nelems-1 && h->A[c] < h->A[c+1])
            c++; 
        if (h->A[k] < h->A[c]) {
          swap(h, k, c);
          k = c;
          c = 2 * c;
        } else {
            break;
        }
        c++;
    }
}

void insert(heap *h, int x)
{
    int k = ++h->nelems;
    perc_up(h, k, x);
}

int deletemax(heap *h)
{
    int x = h->A[1];
    h->nelems--;
    swap(h, 1, h->nelems);
    perc_down(h, 1);
    return x;
}

int level[]  = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
int space[] = {0, 46, 25, 12, 6, 1};
void show(heap *h)
{
    int i, lvl, j;
    int height = 5;
    for (lvl = 0; lvl < 10; lvl++) {
        for (i = 1; i <= level[lvl-1]; i++) {
            if (i + lvl > h->nelems) goto end;
            //printf("<h[%d] = %d>  ", lvl+i, h->A[lvl+i]);
            //for (j = 0; j < space[lvl]; j++) printf(" ");
            printf("<[%d]>  ", h->A[lvl+i]);
        }
        printf("\n");
    }
end:
    return;
}

void show2(heap *h)
{
    int i, lvl;
     for (i = 1; i <= h->nelems; i++) {
        printf("[%d]  ", h->A[i]);
    }
    printf("\n");
}

int a[15] = {22,5,3,4,8,2,7,6,9,11,10,33,20,12,55};
int main()
{
    int i;
    heap *h = create(32);
    for (i = 0; i < 15; i++) {
        insert(h, a[i]);
    }
    show2(h);
    //show(h);
    while (h->nelems) {
        i = deletemax(h);
        printf("max = %d\n", i);
    }
    return 0;
}
