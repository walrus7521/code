#ifndef _GRID_H_
#define _GRID_H_

enum cell_type {DATA, MACRO};

typedef struct grid *grid_ptr;

grid_ptr grid_new(int dim);
void grid_cell_encode(grid_ptr grid, int row, int col, int data, enum cell_type type);
void grid_cell_clr(grid_ptr grid, int row, int col);
void grid_show(grid_ptr grid);

#endif // _GRID_H_

