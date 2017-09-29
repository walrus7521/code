#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// write stories
// sparse matrix: https://en.wikipedia.org/wiki/Sparse_matrix


#define S_DIM (8)

enum cell_type {DATA, MACRO};
struct cell {
    enum cell_type type;
    int data;
    int row;
    int col;
};

struct grid {
    struct cell cells[S_DIM][S_DIM];
};

struct spreadsheet {
    char name[12];
    struct grid cells;
    int size;
    int curr_row;
    int curr_col;  
};

void calc(struct spreadsheet *ss)
{
}

void draw(struct spreadsheet *ss)
{
    int r, c;
    printf("spreadsheet: %s\n", ss->name);
    for (r = 0; r < ss->size; ++r) {
        for (c = 0; c < ss->size; ++c) {
            if (ss->cells.cells[r][c].type == DATA) {
                printf(" %02d |", ss->cells.cells[r][c].data);
            } else {
                printf("  M |");
            }
        }
        printf("\n");
    }
}

void cell_encode(struct cell *c, int row, int col, int data, enum cell_type type)
{
    c->row = row; c->col = col;
    c->data = data;
    c->type = type;
}

void cell_clr(struct cell *c)
{
    c->data = 0;
}

void ss_init(struct spreadsheet *ss, char *name, int size)
{
    int r, c;
    strcpy(ss->name, "avionics");
    ss->size = size;
    for (r = 0; r < ss->size; ++r) {
        for (c = 0; c < ss->size; ++c) {
            cell_clr(&ss->cells.cells[r][c]);
            cell_encode(&ss->cells.cells[r][c], r, c, 0, DATA);
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
    {"show", draw},
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
        if (strncmp("show", line, 4) == 0) draw(ss);
        if (strncmp("calc", line, 4) == 0) calc(ss);
        if (strncmp("set", line, 3) == 0) {
            int row, col, data;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&data);
            cell_encode(&ss->cells.cells[row][col], row, col, data, DATA);
        }
        if (strncmp("mac", line, 3) == 0) {
            int row, col, mac;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&mac);
            cell_encode(&ss->cells.cells[row][col], row, col, mac, MACRO);
        }
        if (strncmp("quit", line, 4) == 0) break;
        printf("ss> ");
    }
    free(line);
    return 0;
}

int main()
{
    struct spreadsheet ss;
    ss_init(&ss, "avionics", S_DIM);
    cli(&ss);
}