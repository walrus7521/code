#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "grid.h"

#define S_DIM (8)

// compile: gcc grid.c sprdsht.c

// write stories
// sparse matrix: https://en.wikipedia.org/wiki/Sparse_matrix

struct spreadsheet {
    char name[12];
    grid_ptr grid;
    int size;
    int curr_row;
    int curr_col;  
};

void calc(struct spreadsheet *ss)
{
}

void ss_init(struct spreadsheet *ss, char *name, int size)
{
    int r, c;
    strcpy(ss->name, "avionics");
    ss->size = size;
    for (r = 0; r < ss->size; ++r) {
        for (c = 0; c < ss->size; ++c) {
            grid_cell_clr(ss->grid, r, c);
            grid_cell_encode(ss->grid, r, c, 0, DATA);
        }
    }
}

void quit(struct spreadsheet *ss)
{
    exit(0);
}

// state machine with dispatchers & help strings
typedef void (*dispatch)(struct spreadsheet *);

struct command {
    char helper[32];
    dispatch handler;
};

int num_commands = 5;
struct command commands[] = 
{
    {"show", NULL},
    {"quit", quit},
    {"set row,col,data", NULL},
    {"mac row,col,mac", NULL},
    {"calc", NULL},
};

void help(struct command *cmds, int len)
{
    int i;
    //printf("help: %d\n", len);
    for (i = 0; i < len; i++) {
        printf("%s\n", cmds[i].helper);
    }
}

int cli(struct spreadsheet *ss)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("ss> ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        //printf("Retrieved line of length %zu : %s\n", read, line);
        if (strncmp("help", line, 4) == 0) help((struct command *) &commands, num_commands);
        else if (strncmp("show", line, 4) == 0) grid_show(ss->grid);
        else if (strncmp("calc", line, 4) == 0) calc(ss);
        else if (strncmp("set", line, 3) == 0) {
            int row, col, data;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&data);
            printf("set: %d %d %d\n", row, col, data);
            grid_cell_encode(ss->grid, row, col, data, DATA);
        }
        else if (strncmp("mac", line, 3) == 0) {
            int row, col, mac;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&mac);
            printf("mac: %d %d %d\n", row, col, mac);
            grid_cell_encode(ss->grid, row, col, mac, MACRO);
        }
        else if (strncmp("quit", line, 4) == 0) break;
        printf("ss> ");
    }
    free(line);
    return 0;
}

int main()
{
    struct spreadsheet ss;
    ss.grid = grid_new(S_DIM);
    ss_init(&ss, "avionics", S_DIM);
    cli(&ss);
}

