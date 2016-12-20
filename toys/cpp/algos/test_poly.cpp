#include <iostream>
#include "Geometry.hpp"


int main()
{
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    //convexHull(points, n);
     
    Polygon p(points, n);
    //p.show();
    p.calc_hull();
}
