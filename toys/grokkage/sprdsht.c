#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#if defined(_WIN64) || defined(_WIN32)
int getline(char **lineptr, size_t *n, FILE *stream)
{
    return 0;

    static char line[256];
    char *ptr;
    unsigned int len;
    if (lineptr == NULL || n == NULL) {
        //errno = -1; //EINVAL;
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
#elif __APPLE__
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
    #elif TARGET_OS_IPHONE
    #else
        #define TARGET_OS_OSX 1
    #endif
#elif __linux
#elif __unix // all unices not caught above
#elif __posix
#endif


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
            grid->cells[r][c].row  = r;
            grid->cells[r][c].col  = c;
            grid->cells[r][c].data = 0;
            grid->cells[r][c].type = DATA;
        }
    }
    return grid;
}

void calc(struct spreadsheet *ss)
{
}

void grid_show(grid_ptr grid)
{
    int r, c;

    printf("    ");
    for (c = 0; c < grid->dim; ++c) 
        printf(" %02d |", c);
    printf("\n");
    printf("    ");
    for (c = 0; c < grid->dim; ++c) 
        printf("---- ");
    printf("\n");

    for (r = 0; r < grid->dim; ++r) {
        printf("%02d] ", r);
        for (c = 0; c < grid->dim; ++c) {
            if (grid->cells[r][c].type == DATA) {
                printf(" %02d |", grid->cells[r][c].data);
            } else {
                printf("  M |");
            }
        }
        printf("\n");
    }
}

void grid_cell_encode(grid_ptr grid, int row, int col, int data, enum cell_type type)
{
    grid->cells[row][col].row  = row; 
    grid->cells[row][col].col  = col;
    grid->cells[row][col].data = data;
    grid->cells[row][col].type = type;
}

void grid_cell_clr(grid_ptr grid, int row, int col)
{
    grid->cells[row][col].data = 0;
}

void ss_init(struct spreadsheet *ss, char *name, int size)
{
    int r, c;
    strcpy(ss->name, "avionics");
    ss->size = size;
    //for (r = 0; r < ss->size; ++r) {
    //    for (c = 0; c < ss->size; ++c) {
    //        grid_cell_clr(ss->grid, r, c);
    //        grid_cell_encode(ss->grid, r, c, 0, DATA);
    //    }
    //}
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

