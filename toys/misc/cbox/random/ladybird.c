#include <stdio.h>

#define LADYBIRD (0)
#define CATPILL  (1)

#define WIDTH    (0)
#define LENGTH   (1)

// y = length
// x = width

float coords[2][2] = {{3,1},  // LADYBIRD
                      {1,3}}; // CATPILL
float y_desired = 1.1; // just above the ladybird line
float A;
float delta_A;
float Error;

void show(float a[2][2], int id)
{
    printf("(%.1f, %.1f)\n", a[id][WIDTH], a[id][LENGTH]);
}

void test(float a[2][2], int id)
{
    float x_truth = a[id][WIDTH];
    float y_truth = a[id][LENGTH];
    float y_length = A * x_truth;

    printf("(%.2f, %.2f)\n", x_truth, y_length);
    if (y_length < y_truth) {
        Error = y_desired - y_length;
        delta_A = Error / x_truth;
        printf("%.2f is too small, y must be at least %.2f, error is %.2f -> delta A is %.2f\n", A, y_desired, Error, delta_A);
        
    } else {
        printf("(%.2f, %.2f) seems close, using A = %.4f\n", x_truth, y_length, A);
    }
}

int main()
{
    show(coords, LADYBIRD);
    show(coords, CATPILL);
    A = 0.25;
    test(coords, LADYBIRD);
    // retry
    A += delta_A;
    test(coords, LADYBIRD);

}
