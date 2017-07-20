#include <stdio.h>
#include <stdlib.h>

void show(char **a, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%c ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void input()
{
  int rows, cols, i, j;
  char **a;
  char c;
  scanf("%d %d", &rows, &cols);
  printf("rows: %d, cols: %d\n", rows, cols);

  a = (char **) malloc(rows * sizeof(char *));
  for (i = 0; i < rows; i++) {
    a[i] = (char*) malloc(cols * sizeof(char));
  }

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      a[i][j] = (char) ('a'+i+j);
      //scanf("%c", &c);
      //a[i][j] = c;
    }
  }

  show(a, rows, cols);
}

int main()
{
  input();
}
