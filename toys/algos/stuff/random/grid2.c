#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph2.h"

#define BLOCKING '*'
#define OPEN     '.'

typedef struct {
    int key;
    char val;
    int row, col;
} vertex_t;

typedef struct {
    int nrows, ncols, nverts;
    vertex_t **B;
    graph *grph;
} grid_t;

grid_t *create_grid(int rows, int cols)
{
    int r, c;
    grid_t *g = (grid_t *) malloc(sizeof(grid_t));
    g->nrows = rows;
    g->ncols = cols;

    g->B = (vertex_t **) malloc(sizeof(vertex_t *) * (rows+2));
    for (r = 0; r < rows+2; r++) {
        g->B[r] = (vertex_t *) malloc(sizeof(vertex_t) * (cols+2));
    }

    for (r = 0; r < rows+2; r++)
        for (c = 0; c < cols+2; c++)
            g->B[r][c].val = BLOCKING;

    printf("create_grid: nrows %d, ncols %d\n", g->nrows, g->ncols);
    return g;
}

void show_grid(grid_t *g)
{
    int row, col, v;
    for (row = 1; row <= g->nrows; row++) {
        printf("[%03d]: ", row);
        for (col = 1; col <= g->ncols; col++) {
            printf("%c", g->B[row][col].val);
        }
        printf("\n");
    }
    printf("\n");
    printf("grid of vertices new:\n");
    for (row = 1; row <= g->nrows; row++) {
        printf("[%03d]: ", row);
        for (col = 1; col <= g->ncols; col++) {
            printf("%03d ", g->B[row][col].key);
        }
        printf("\n");
    }
    printf("\n");
}

void add_edge(grid_t *g, int v1, int v2)
{
    insert_edge(g->grph, v1, v2, 1);
}

void grid_to_graph(grid_t *g)
{
    int row, col;
    vertex_t vt, vt1, vt2, vt3, vt4, vt5, vt6, vt7, vt8;
    g->grph = graph_create();
    g->grph->nvertices = g->nverts;
    for (row = 1; row <= g->nrows; row++) {
        for (col = 1; col <= g->ncols; col++) {
            vt = g->B[row][col];
            printf("[%d][%d] => v = %d => %c\n", row, col, vt.key, vt.val); // shows hose mode here
            if (vt.val != BLOCKING) {
                vt1 = g->B[row-1][col-1];
                vt2 = g->B[row-1][col];
                vt3 = g->B[row-1][col+1];
                vt4 = g->B[row][col-1];
                vt5 = g->B[row][col+1];
                vt6 = g->B[row+1][col-1];
                vt7 = g->B[row+1][col];
                vt8 = g->B[row+1][col+1];

                if (vt1.val != BLOCKING) {
                    add_edge(g, vt.key, vt1.key);
                }
                if (vt2.val != BLOCKING) {
                    add_edge(g, vt.key, vt2.key);
                }
                if (vt3.val != BLOCKING) {
                    add_edge(g, vt.key, vt3.key);
                }
                if (vt4.val != BLOCKING) {
                    add_edge(g, vt.key, vt4.key);
                }
                if (vt5.val != BLOCKING) {
                    add_edge(g, vt.key, vt5.key);
                }
                if (vt6.val != BLOCKING) {
                    add_edge(g, vt.key, vt6.key);
                }
                if (vt7.val != BLOCKING) {
                    add_edge(g, vt.key, vt7.key);
                }
                if (vt8.val != BLOCKING) {
                    add_edge(g, vt.key, vt8.key);
                }

            }
        }
    }
}

int getlines(grid_t *g)
{
    int row, col;
    char c;
    vertex_t *v;
    for (row = 1; row <= g->nrows; row++) {
        /* add 1 to loop to grab the carriage return */
        for (col = 1; col <= g->ncols+1; col++) {
            c = (char) getchar();
            if (c != OPEN && c != BLOCKING) {
                //printf("what is it c = %c, x = %x\n", c, c);
                continue;
            }
            g->B[row][col].key = ((g->ncols+2)*row)+col;
            g->B[row][col].val = c;
            g->B[row][col].row = row;
            g->B[row][col].col = col;
            //printf("[%d][%d] = %c\n", row, col, g->A[row][col]);
        }
    }
    g->nverts = (g->nrows+2) * (g->ncols+2);
    return 0;
}

int main()
{
    int nrows, ncols, i;
    grid_t *g;
    nrows = ncols = 0;
    while (EOF != scanf("%d %d\n", &nrows, &ncols)) {
        if (nrows == 0 && ncols == 0) break;
        g = create_grid(nrows, ncols);
        //printf("nrows = %d, ncols = %d\n", nrows, ncols);
        getlines(g);
        printf("show grid:\n");
        printf("==========\n");
        show_grid(g);
        grid_to_graph(g);
        printf("show graph of pathways:\n");
        printf("============================================\n");
        //show(g->grph);
        print_graph(g->grph);
        initialize_search(g->grph);
        bfs(g->grph, 121);
        printf("============================================\n");
        for (i = 0; i < g->nverts; i++)
            printf("parents[%d] = %d\n", i, parent[i]);

        find_path(121, 22, parent);
        printf("\n");
        nrows = ncols = 0;
    }

    return 0;
}


