/* The open doors problem
 * Five hundred closed doors along a corridor are numbered from 1 to 500.  A person
 * walks through the corridor and opens each door.  Another person walks through the
 * corridor and closes every alternate door.  Continuing in the manner, the i-th person
 * comes and toggles the position of every i-th door starting from door i.
 *
 * Which doors are open after the 500-th person has walked through?
 */

#include <iostream>

using namespace std;

#define N_DOORS 50
#define OPEN   0
#define CLOSED 1
int doors[500] = {0};

void show()
{
    for (int i = 1; i < N_DOORS; ++i) {
        printf("doors[%02d] = %d\n", i, doors[i]);
    }
}

void predict_open(int k, int n)
{
    printf("door[1]\n");
    for (int d = 2; d*d < n; ++d) {
        printf("door[%d]\n", d*d);
    }
}

int main()
{
    int outer;
    //predict_open(5, 500);
    //return 0;
    for (int i = 1; i < N_DOORS; ++i) {
        doors[i] = OPEN;
    }
    for (int p = 2; p < N_DOORS; ++p) {
        cout << "p: " << p << endl;
        for (int i = p; i < N_DOORS; ++i) {
            if ((i % p) == 0) {
                doors[i] ^= 1;
            }
        }
        show();
    }
   
}
