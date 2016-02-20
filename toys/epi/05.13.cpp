#include <stdio.h>

/* A rectangle whose sides are parallel to the X-axis and Y-axis can be represented by
 * its left-most lower point (x,y), width w, and height h.  This problem is concerned
 * with such rectangles.
 *
 * Write a function which tests if two rectangles have a nonempty intersection.  If the
 * intersection is nonempty, return the rectangle formed by their intersection.
 */

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct rect {
    int x, y, width, height;
} rect;

rect *min_rect(rect& R, rect& S)
{
    rect *r = new(rect);
    int x1, y1, x2, y2;

    x1 = MAX(R.x, S.x);
    x2 = MIN(R.x+R.width, S.x+S.width);
    y1 = MAX(R.y, S.y);
    y2 = MIN(R.y+R.height, S.y+S.height);

    r->x = x1;
    r->width = x2-x1;
    r->y = y1;
    r->height = y2-y1;

    return r;
}

int intersect2(rect& R, rect& S)
{
    return ((R.x <= S.x + S.width)  && (R.x + R.width >= S.x) &&
            (R.y <= S.y + S.height) && (R.y + R.height >= S.y)); 
}

void show(rect& r)
{
    printf("rect: (x1, y1) (x2, y2)\n");
    printf("      (%d, %d) (%d, %d)\n", r.x, r.y, r.x+r.width, r.y+r.height);
}

int main()
{
    rect a = {4,4,0,17};
    rect b = {2,2,22,22};
    rect c = {2,14,11,11};
    rect d = {11,2,12,12};
    rect e = {7,10,8,8};
    printf("intersect: %d\n", intersect2(a, b));
    printf("intersect: %d\n", intersect2(a, c));
    printf("intersect: %d\n", intersect2(a, d));
    printf("intersect: %d\n", intersect2(a, e));
    rect *r = min_rect(a, b);
    show(*r);
}

