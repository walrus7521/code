/*
    Area = sqrt(s*(s-a)*(s-b)*(s-c))
    where a, b and c are lengths of sides of
    triangle and s = (a+b+c)/2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
/* PC by Skiena
 *
 * also see http://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
 */
float areaTriangleFromCoords(float ax, float ay, float bx, float by, float cx, float cy)
{
    float area;
    area = (((ax * by) - (ay * bx) + (ay * cx) -
             (ax * cy) + (bx * cy) - (cx * by)) / 2.0);
    return fabs(area);
}

/*
 * http://quiz.geeksforgeeks.org/c-program-find-area-triangle/
 */
float areaTriangleFromLengths(int a, int b, int c)
{
     // Length of sides must be positive and sum of any two sides
     // must be smaller than third side.
    if (a < 0 || b < 0 || c <0 || (a+b <= c) ||
        a+c <=b || b+c <=a)
    {
        printf("Not a valid triangle\n");
        exit(0);
    }
    int s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
 
int main()
{
    /* lengths of sides */
    int a = 3;
    int b = 4;
    int c = 5;
 
    printf("Area is %f\n", areaTriangleFromLengths(a, b, c));
    printf("Area is %f\n", areaTriangleFromCoords(0,0,3,0,0,4));
    return 0;
}
