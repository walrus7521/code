#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// https://brennan.io/2015/01/16/write-a-shell-in-c/

char **game;
int rows;
int cols;

void show()
{
  int i, j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%c", game[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void draw()
{
    show();
}

void input(char *fname)
{
  int i, j;
  char c;
  FILE *fp;
  printf("input: %s len %d\n", fname, strlen(fname));
  fp = fopen(fname, "r");
  if (fp == NULL) {
      printf("error opening %s\n", fname);
      return;
  }
  fscanf(fp, "%d %d", &rows, &cols);
  printf("rows: %d, cols: %d\n", rows, cols);

  game = (char **) malloc(rows * sizeof(char *));
  for (i = 0; i < rows; i++) {
    game[i] = (char*) malloc(cols * sizeof(char));
  }

  for (i = 0; i < rows; i++) {
      fscanf(fp, "%s", game[i]);
      //printf("%s\n", game[i]);
  }

  show(rows, cols);
}

char *chomp(char *line)
{
    line[strlen(line)-1] = '\0';
    return line;
}

char parse(char *line)
{
    if (strstr(line, "quit")) return 'q';
    if (strstr(line, "load")) return 'l';
    if (strstr(line, "help")) return 'h';
}

void usage()
{
    printf(" help\n");
    printf(" load <input file>\n");
    printf(" quit\n");
}

#define MAX_LENGTH 1024
int main(int argc, char *argv[]) {
  char line[MAX_LENGTH];

  while (1) {
    printf("$ ");
    if (!fgets(line, MAX_LENGTH, stdin)) break;
    switch (parse(line)) {
        case 'l':
            printf("enter file name: ");
            if (!fgets(line, MAX_LENGTH, stdin)) break;
            input(chomp(line));
            show();
            break;
        case 'q':
            printf("bye\n");
            return 0;
        case 'h':
            usage();
            break;
    }
  }

  return 0;
}


