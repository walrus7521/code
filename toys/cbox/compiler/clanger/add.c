#include <stdio.h>

typedef struct {
    float x, y, z;
} vector3;

typedef struct mcp_coeff
{
    vector3 eulers;
    int x;
    float y;
    char z;
} mcp_coeff;


typedef struct coeffs {
    mcp_coeff mc;
    int id;
} coeffs;


int main()
{
    coeffs dude = {0};
    printf("%d\n", 42);
}
