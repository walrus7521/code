#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int getline(char **lineptr, size_t *n, FILE *stream)
{
    return 0;

    static char line[256];
    char *ptr;
    unsigned int len;
    if (lineptr == NULL || n == NULL) {
        errno = -1; //EINVAL;
        return -1;
    }
    if (ferror (stream)) return -1;
    if (feof(stream)) return -1;
    fgets(line,256,stream);
    ptr = strchr(line,'\n');   
    if (ptr) *ptr = '\0';
    len = strlen(line);
    if ((len+1) < 256) {
        ptr = realloc(*lineptr, 256);
        if (ptr == NULL) return(-1);
        *lineptr = ptr;
        *n = 256;
    }
    strcpy(*lineptr,line); 
    return(len);
}

typedef struct grid *grid_ptr;

// write stories
// sparse matrix: https://en.wikipedia.org/wiki/Sparse_matrix

#define S_DIM (8)

enum cell_type {DATA, MACRO};
struct cell {
    enum cell_type type;
    int data;
    int row;
    int col;
} cell;

struct grid {
    int dim;
    struct cell **cells; //[S_DIM][S_DIM];
} grid;

struct spreadsheet {
    char name[12];
    grid_ptr grid;
    int size;
    int curr_row;
    int curr_col;  
};


grid_ptr grid_new(int dim)
{
    int r, c;
    grid_ptr grid = malloc(sizeof(*grid));
    grid->dim = dim;
    grid->cells = (struct cell **) malloc(grid->dim * sizeof(struct cell));
    for (r = 0; r < grid->dim; ++r) {
        grid->cells[r] = (struct cell *) malloc(sizeof(struct cell));
    }
    for (r = 0; r < grid->dim; ++r) {
        for (c = 0; c < grid->dim; ++c) {
            //grid->cells[r][c].row  = r;
            //grid->cells[r][c].col  = c;
            grid->cells[r][c].data = 0;
            grid->cells[r][c].type = DATA;
        }
    }
    return grid;
}

void calc(struct spreadsheet *ss)
{
}

void draw(struct spreadsheet *ss)
{
    int r, c;
    printf("spreadsheet: %s\n", ss->name);
    for (r = 0; r < ss->size; ++r) {
        for (c = 0; c < ss->size; ++c) {
            if (ss->grid->cells[r][c].type == DATA) {
                printf(" %02d |", ss->grid->cells[r][c].data);
            } else {
                printf("  M |");
            }
        }
        printf("\n");
    }
}

void cell_encode(struct cell *c, int row, int col, int data, enum cell_type type)
{
    //c->row = row; c->col = col;
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
            cell_clr(&ss->grid->cells[r][c]);
            cell_encode(&ss->grid->cells[r][c], r, c, 0, DATA);
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
#if 0
        printf("Retrieved line of length %zu : %s\n", read, line);
        if (strncmp("help", line, 4) == 0) help((struct command *) &commands, num_commands);
        else if (strncmp("show", line, 4) == 0) draw(ss);
        else if (strncmp("calc", line, 4) == 0) calc(ss);
        else if (strncmp("set", line, 3) == 0) {
            int row, col, data;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&data);
            cell_encode(&ss->grid->cells[row][col], row, col, data, DATA);
        }
        else if (strncmp("mac", line, 3) == 0) {
            int row, col, mac;
            sscanf(&line[4], "%d,%d,%d", &row,&col,&mac);
            cell_encode(&ss->grid->cells[row][col], row, col, mac, MACRO);
        }
        else if (strncmp("quit", line, 4) == 0) break;
#endif
        printf("ss> ");
    }
    free(line);
    return 0;
}

int main()
{
    struct spreadsheet ss;
    ss.grid = grid_new(S_DIM);
    //ss_init(&ss, "avionics", S_DIM);
    cli(&ss);
}

