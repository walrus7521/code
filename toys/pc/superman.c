#include <stdio.h>
#include <math.h>
#include "geometry.h"

#define MAXN 100

point s;
point t;
int ncircles;
circle c[MAXN];

void superman()
{
    line l;
    point close;
    double d;
    double xray = 0.0;
    double around = 0.0;
    double angle;
    double travel;
    int i;
    double asin(), sqrt();
    double distance();

    points_to_line(s, t, &l);

    for (i = 1; i <= ncircles; i++) {
        closest_point(c[i].c, l, close);
        d = distance(c[i].c, close);
        if ((d >= 0) && (d < c[i].r) && point_in_box(close, s, t)) {
            xray += 2 * sqrt(c[i].r * c[i].r - d*d);
            angle = acos(d/c[i].r);
            around += ((2*angle)/(2*PI)) * (2*PI*c[i].r);
        }
    }
    travel = distance(s, t) - xray + around;
    printf("Superman sees thru %7.3lf units, and flies %7.3lf units\n",
            xray, travel);

}

int main()
{
    superman();
    return 0;
}
