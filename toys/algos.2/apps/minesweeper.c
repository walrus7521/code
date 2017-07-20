#include <stdio.h>
#include <stdlib.h>

void show(int **a, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void fill(int **a, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      a[i][j] = i+j;
    }
  }
}

void input()
{
  int rows, cols, i;
  int **a;
  scanf("%d %d", &rows, &cols);
  printf("rows: %d, cols: %d\n", rows, cols);

  a = (int **) malloc(rows * sizeof(int *));
  for (i = 0; i < rows; i++) {
    a[i] = (int*) malloc(cols * sizeof(int));
  }
  fill(a, rows, cols);
  show(a, rows, cols);
}

int main()
{
  input();
}
