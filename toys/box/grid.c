#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "grid.h"

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
        grid_to_vertices(g);
        //show_vertices(g);
        //show_vertices2(g);
        grid_to_graph(g);
        printf("show graph of pathways:\n");
        printf("============================================\n");
        //show(g->grph);
        print_graph(g->grph);
        initialize_search(g->grph);
        bfs(g->grph, 24);
        printf("============================================\n");
        for (i = 0; i < g->nverts; i++)
            printf("parents[%d] = %d\n", i, parent[i]);

        find_path(121, 22, parent);
        printf("\n");
        nrows = ncols = 0;
    }

    return 0;
}

