#include <stdio.h>

typedef struct rect {
    int x, y, width, height;
} rect;

int intersect2(rect& R, rect& S)
{
    return ((R.x <= S.x + S.width)  && (R.x + R.width >= S.x) &&
            (R.y <= S.y + S.height) && (R.y + R.height >= S.y)); 
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
}

