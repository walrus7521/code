#include <stdio.h>


typedef struct point {
    int x,y;
} point;

// stash off minimum bounding rectangle
int minx, maxx, miny, maxy;

#define VERTS 5
int pix[VERTS][VERTS] = {
              { 2, 0, 4, 6, 0 }, 
              { 0, 0, 1, 4, 0 }, 
              { 5, 0, 0, 8, 0 }, 
              { 1, 0, 0, 8, 0 }, 
              { 0, 1, 0, 0, 0 } };

int viz[VERTS][VERTS] = {
              { 0, 0, 0, 0, 0 }, 
              { 0, 0, 0, 0, 0 }, 
              { 0, 0, 0, 0, 0 }, 
              { 0, 0, 0, 0, 0 }, 
              { 0, 0, 0, 0, 0 } };

point stack[32];
int top = 0;
int n   = 0;
void push(point p)
{
    // boundary checks
    if ((p.x >= 0 && p.x < VERTS) &&
        (p.y >= 0 && p.y < VERTS)) {

        stack[top++] = p;
    }
}

point pop()
{
    point p = stack[--top];
    return p;
}

int empty()
{
    return (top == 0);
}

void show_pic()
{
    int r, c;
    for (r = 0; r < VERTS; r++) {
        for (c = 0; c < VERTS; c++) {
            printf("%d ", pix[r][c]);
        }
        printf("\n");
    }
}

void show(point p)
{
    printf("[%02d,%02d] = %02d\n", p.x, p.y, pix[p.x][p.y]);
}


void connec(point p)
{
    point tmp;
    // capture min and max
    if (minx > p.x) minx = p.x;
    if (maxx < p.x) maxx = p.x;
    if (miny > p.y) miny = p.y;
    if (maxy < p.y) maxy = p.y;
    // north
    tmp.x = p.x;   tmp.y = p.y-1; push(tmp);
    // south
    tmp.x = p.x;   tmp.y = p.y+1; push(tmp);
    // east
    tmp.x = p.x-1; tmp.y = p.y;   push(tmp);
    // west
    tmp.x = p.x+1; tmp.y = p.y;   push(tmp);

}

int main()
{
    int r, c, color=0, count = 0;;
    int newcolor = 7;
    minx = miny = 99999;
    maxx = maxy = 0;
    show_pic();
    point start = {1,1};
    push(start);
    while (!empty()) {
        point p = pop();
        if (pix[p.x][p.y] == color) {
            show(p);
            connec(p);
            // set new color
            pix[p.x][p.y] = newcolor;

            count++;
        }
    }
    printf("count: %d\n", count);
    printf("min bounding rectangle: ");
    printf("min(%d,%d): max(%d,%d)\n", minx, miny, maxx, maxy);
    show_pic();
}


