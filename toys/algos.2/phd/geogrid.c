#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

// types
#define MAXN 32
#define PI 3.141592
#define EPSILON (.001)
#define X (0)
#define Y (1)
#define TRUE (1)
#define FALSE (0)

typedef double point[2];    

typedef struct {
    double a;
    double b;
    double c;
} line;

typedef struct {
    point c; /* center of circle */
    double r; /* radius of circle */
} circle;

void points_to_line(point p1, point p2, line *l)
{
    if (p1[X] == p2[X]) {
        l->a = 1;
        l->b = 0;
        l->c = -p1[X];
    } else {
        l->b = 1;
        l->a = -(p1[Y]-p2[Y])/(p1[X]-p2[X]);
        l->c = -(l->a * p1[X]) - (l->b * p1[Y]);
    }
}

void point_and_slope_to_line(point p, double m, line *l)
{
    l->a = -m;
    l->b = 1;
    l->c = -((l->a*p[X]) + (l->b*p[Y]));
}

bool parallelQ(line l1, line l2)
{
    return ( (fabs(l1.a-l2.a) <= EPSILON) &&
    (fabs(l1.b-l2.b) <= EPSILON) );
}
bool same_lineQ(line l1, line l2)
{
    return ( parallelQ(l1,l2) && (fabs(l1.c-l2.c) <= EPSILON) );
}

void intersection_point(line l1, line l2, point p)
{
    if (same_lineQ(l1,l2)) {
        printf("Warning: Identical lines, all points intersect.\n");
        p[X] = p[Y] = 0.0;
        return;
    }
    if (parallelQ(l1,l2) == TRUE) {
        printf("Error: Distinct parallel lines do not intersect.\n");
        return;
    }
    p[X] = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
    if (fabs(l1.b) > EPSILON) /* test for vertical line */
        p[Y] = - (l1.a * (p[X]) + l1.c) / l1.b;
    else
        p[Y] = - (l2.a * (p[X]) + l2.c) / l2.b;
}

void closest_point(point p_in, line l, point p_c)
{
    line perp; /* perpendicular to l through (x,y) */
    if (fabs(l.b) <= EPSILON) { /* vertical line */
        p_c[X] = -(l.c);
        p_c[Y] = p_in[Y];
        return;
    }
    if (fabs(l.a) <= EPSILON) { /* horizontal line */
        p_c[X] = p_in[X];
        p_c[Y] = -(l.c);
        return;
    }
    point_and_slope_to_line(p_in,1/l.a,&perp); /* normal case */
    intersection_point(l,perp,p_c);
}

double signed_triangle_area(point a, point b, point c)
{
    return( (a[X]*b[Y] - a[Y]*b[X] + a[Y]*c[X]
            - a[X]*c[Y] + b[X]*c[Y] - c[X]*b[Y]) / 2.0 );
}

double triangle_area(point a, point b, point c)
{
    return( fabs(signed_triangle_area(a,b,c)) );
}

double distance(point a, point b)
{
    double dx = a[X]-b[X];
    double dy = a[Y]-b[Y];
    double dz = sqrt(dx*dx + dy*dy);
    return dz;
}

bool point_in_box(point p, point b1, point b2)
{
    return( (p[X] >= min(b1[X],b2[X])) && (p[X] <= max(b1[X],b2[X]))
            && (p[Y] >= min(b1[Y],b2[Y])) && (p[Y] <= max(b1[Y],b2[Y])) );
}

point s; /* Supermanís initial position */
point t; /* target position */
int ncircles; /* number of circles */
circle c[MAXN]; /* circles data structure */
void superman()
{
    line l; /* line from start to target position */
    point close; /* closest point */
    double d; /* distance from circle-center */
    double xray = 0.0; /* length of intersection with circles */
    double around = 0.0; /* length around circular arcs */
    double angle; /* angle subtended by arc */
    double travel; /* total travel distance */
    int i; /* counter */

    // init
    s[X] = 0.0; s[Y] = 0.0;
    t[X] = 10.0; t[Y] = 10.0;
    ncircles = 4;
    c[0].c[X] = 0; c[0].c[X] = 0; c[0].r = 3;
    c[1].c[X] = 0; c[1].c[X] = 0; c[1].r = 3;
    c[2].c[X] = 0; c[2].c[X] = 0; c[2].r = 3;
    c[3].c[X] = 0; c[3].c[X] = 0; c[3].r = 3;

    points_to_line(s,t,&l);
    for (i=1; i<=ncircles; i++) {
        closest_point(c[i].c,l,close);
        d = distance(c[i].c,close);
        printf("distance: %f\n", d);
        if ((d>=0) && (d < c[i].r) && point_in_box(close,s,t)) {
            xray += 2*sqrt(c[i].r*c[i].r - d*d);
            angle = acos(d/c[i].r);
            around += ((2*angle)/(2*PI)) * (2*PI*c[i].r);
        }
    }
    travel = distance(s,t) - xray + around;
    printf("Superman sees thru %7.3lf units, and flies %7.3lf units\n", xray, travel);
}

void grid_show(int rows, int cols, int p[][cols], char *name) {
    int i, j;
    printf("graph: %s\n", name);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
}

void row_major(int rows, int cols, int a[][cols])
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d %d\n", i, j);
        }
        printf("\n");
    }
}

void col_major(int rows, int cols, int a[][cols])
{
    int i, j;
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            printf("%d %d\n", i, j);
        }
        printf("\n");
    }
}

void snake(int rows, int cols, int a[][cols])
{
    int i, j, k;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            k = j + (cols-2*j-1) * (i%2);
            printf("%d %d\n", i, k);
        }
        printf("\n");
    }
}

// BUGBUG
void diagonal_orig(int rows, int cols, int a[][cols])
{
    int d, j, k, hgt, pcnt, l1, l2;
    for (d = 0; d < rows+cols; d++) {
        //printf("d1: %d\n", d);
        hgt = 1 + max(0,(d-cols));
        printf("hgt: %d\n", hgt);
        //printf("d2: %d\n", d);
        //hgt = max(0,(d-cols));
        pcnt = min(d, (rows-hgt+1));
        printf("pcnt: %d\n", pcnt);
        for (j = 0; j < pcnt; j++) {
            //printf("cols: %d, d: %d\n", cols, d);
            l1 = min(cols,d)-j;
            l2 = hgt+j;
            printf("%d %d\n", l1, l2);
        }
        printf("\n");
    }
}

void diagonal(int rows, int cols, int a[][cols])
{
    int d, j, k;
    int hgt; // row of lowest point
    int pcnt; // points on diagonal
    int l1, l2; // final coordinates

    for (d = 0; d < rows+cols; d++) {
        printf("d-cols: %d\n", (d-cols));
        hgt = max(0,(d-cols));
        printf("hgt: %d\n", hgt);
        //hgt = max(0,(d-cols));
        pcnt = 1 + min(d, (rows-hgt+1));
        printf("pcnt: %d\n", pcnt);
        for (j = 0; j < pcnt; j++) {
            //printf("cols: %d, d: %d\n", cols, d);
            l1 = min(cols,d)-j;
            l2 = hgt+j;
            printf("%d %d\n", l1, l2);
        }
        printf("\n");
    }
}

void traversals()
{
    int s[][4] = { {  1,  2,  3,  4 }, 
                   {  5,  6,  7,  8 }, 
                   {  9, 10, 11, 12 }, 
                   { 13, 14, 15, 16 } };

    //col_major(4,4,s);
    //row_major(4,4,s);
    //snake(4,4,s);
    //diagonal_orig(4,4,s);
    diagonal(4,4,s);
    grid_show(4,4,s,"snake");
 }

int main()
{
    traversals();
    superman();
}
