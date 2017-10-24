#include <stdio.h>

// create a table for interp'ing

float interp_segment(float x0, float y0, float x1, float y1, float x)
{
    float t;

    if (x <= x0) { return y0; }
    if (x >= x1) { return y1; }

    t =  (x-x0);
    t /= (x1-x0);

    return y0 + t*(y1-y0);
}

int main()
{
    float x[] = {0.00000, 0.78540, 1.57080, 2.35619, 3.14159, 
                 3.92699, 4.71239, 5.49779, 6.28319};
    float y[] = {0.00000, 0.70711, 1.00000, 0.70711, 0.00000, 
                -0.70711, -1.00000, -0.70711, -0.00000};

    int num_pts = 9;

    int i = 0;
    int j = 1;
    float res = interp_segment(x[i],y[i],x[j],y[j], 0.5);
    printf("res=%f\n", res);

}
