#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph2.h"

#define BLOCKING '*'
#define OPEN     '.'

typedef struct {
    int row, col;
} cell;

typedef struct {
    int nr;
    char val;
    int row, col;
} vertex_t;

typedef struct {
    int nrows, ncols, nverts;
    int **A;
    vertex_t *v;
    graph *grph;
} grid_t;

grid_t *create_grid(int rows, int cols)
{
    int r, c;
    grid_t *g = (grid_t *) malloc(sizeof(grid_t));
    g->nrows = rows;
    g->ncols = cols;
    g->A = (int **) malloc(sizeof(int *) * (rows+2));
    for (r = 0; r < rows+2; r++) {
        g->A[r] = (int *) malloc(sizeof(int) * (cols+2));
    }
    for (r = 0; r < rows+2; r++)
        for (c = 0; c < cols+2; c++)
            g->A[r][c] = BLOCKING;
    printf("create_grid: nrows %d, ncols %d\n", g->nrows, g->ncols);
    return g;
}

int get_vertex(grid_t *g, int row, int col)
{
    int v;
    v = ((g->ncols+2) * row) + col;
    //printf("get_vertex[%d][%d] = %d\n", row, col, v);
    return v;
}

int get_row_col(grid_t *g, int vertex, cell *cell)
{
    cell->row = vertex / g->ncols;
    cell->col = vertex - (g->ncols * cell->row);
    return 0;
}

void show_grid(grid_t *g)
{
    int row, col, v;
    for (row = 1; row <= g->nrows; row++) {
        printf("[%03d]: ", row);
        for (col = 1; col <= g->ncols; col++) {
            printf("%c", g->A[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    printf("grid of vertices:\n");
    printf("       ");
    for (col = 1; col <= g->ncols; col++) 
        printf("%03d ", col);
    printf("\n       =======================================\n");
    for (row = 1; row <= g->nrows; row++) {
        printf("[%03d]: ", row);
        for (col = 1; col <= g->ncols; col++) {
            v =  get_vertex(g, row, col);
            printf("%03d ", v);
        }
        printf("\n");
    }
    printf("\n");
}

void grid_to_vertices(grid_t *g) {
    int row, col, vrtx;
    int row_cols = (g->nrows+2) * (g->ncols+2);
    int size = sizeof(vertex_t) * row_cols;
    vertex_t *v;
    g->v = (vertex_t *) malloc(size);
    v = g->v;
    memset(v, size, 0);
    v->nr = row_cols;
    g->nverts = row_cols;
    for (row = 0; row <= g->nrows+1; row++) {
        for (col = 0; col <= g->ncols+1; col++) {
            vrtx = get_vertex(g, row, col);
            v[vrtx].val = g->A[row][col];
            v[vrtx].row = row;
            v[vrtx].col = col;
            //printf("vertex[%d][%d] = %d -> %c\n", row, col, vrtx, g->A[row][col]);
            //printf("vertex[%d][%d] = %d -> %c\n", v[vrtx].row, v[vrtx].col, vrtx, v[vrtx].val);
        }
    }
}

void show_vertices(grid_t *g)
{
    int i;
    vertex_t *vr, *v;
    v = g->v;
    printf("show_vertices - enter\n");
    printf("nr vertices = %d = %d\n", v->nr, g->nverts);
    for (i = 0; i < v->nr; i++) {
        vr = &v[i];
        printf("[%d][%d] => v = %d => %c\n", vr->row, vr->col, i, vr->val);
        //printf("[%d][%d] => v = %d => %c\n", vr->row, vr->col, i, vr->val);
    }
    printf("show_vertices - exit\n");
}

void show_vertices2(grid_t *g)
{
    int row, col, v;
    printf("show_vertices #2 - enter\n");
    for (row = 0; row <= g->nrows+1; row++) {
        for (col = 0; col <= g->ncols+1; col++) {
            v  = get_vertex(g, row, col);
            printf("[%d][%d] => v = %d => %c\n", row, col, v, g->v[v].val); // shows hose mode here
        }
    }
    printf("show_vertices #2 - exit\n");
}

void add_edge(grid_t *g, int v1, int v2)
{
    //printf("add_edge: %d -> %d\n", v1, v2);
    //add_edge_wt(g->grph, v1, v2, 1);
    insert_edge(g->grph, v1, v2, 1);
}

void grid_to_graph(grid_t *g)
{
    int row, col, v;
    int v1, v2, v3, v4, v5, v6, v7, v8;
    //g->grph = create(g->nverts);
    g->grph = graph_create();
    g->grph->nvertices = g->nverts;
    for (row = 1; row <= g->nrows; row++) {
        for (col = 1; col <= g->ncols; col++) {
            v  = get_vertex(g, row,   col);
            printf("[%d][%d] => v = %d => %c\n", row, col, v, g->v[v].val); // shows hose mode here
            if (g->v[v].val != BLOCKING) {
                v1 = get_vertex(g, row-1, col-1);
                v2 = get_vertex(g, row-1, col);
                v3 = get_vertex(g, row-1, col+1);
                v4 = get_vertex(g, row,   col-1);
                v5 = get_vertex(g, row,   col+1);
                v6 = get_vertex(g, row+1, col-1);
                v7 = get_vertex(g, row+1, col);
                v8 = get_vertex(g, row+1, col+1);
#if 0
                printf("v1 = %d\n", v1);
                printf("v1 = %d\n", v2);
                printf("v1 = %d\n", v3);
                printf("v1 = %d\n", v4);
                printf("v1 = %d\n", v5);
                printf("v1 = %d\n", v6);
                printf("v1 = %d\n", v7);
                printf("v1 = %d\n", v8);
                printf("\n");
#endif
                if (g->v[v1].val != BLOCKING) {
                    add_edge(g, v, v1);
                }
                if (g->v[v2].val != BLOCKING) {
                    add_edge(g, v, v2);
                }
                if (g->v[v3].val != BLOCKING) {
                    add_edge(g, v, v3);
                }
                if (g->v[v4].val != BLOCKING) {
                    add_edge(g, v, v4);
                }
                if (g->v[v5].val != BLOCKING) {
                    add_edge(g, v, v5);
                }
                if (g->v[v6].val != BLOCKING) {
                    add_edge(g, v, v6);
                }
                if (g->v[v7].val != BLOCKING) {
                    add_edge(g, v, v7);
                }
                if (g->v[v8].val != BLOCKING) {
                    add_edge(g, v, v8);
                }
            }
        }
    }
}

int getlines(grid_t *g)
{
    int row, col;
    char c;
    for (row = 1; row <= g->nrows; row++) {
        /* add 1 to loop to grab the carriage return */
        for (col = 1; col <= g->ncols+1; col++) {
            c = (char) getchar();
            if (c != OPEN && c != BLOCKING) {
                //printf("what is it c = %c, x = %x\n", c, c);
                continue;
            }
            g->A[row][col] = c;
            //printf("[%d][%d] = %c\n", row, col, g->A[row][col]);
        }
    }
    return 0;
}

int grid_test()
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
        grid_to_vertices(g);
        //show_vertices(g);
        //show_vertices2(g);
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

