#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int i, N, result; 
    scanf("%d",&N);

    if (N >= 2 && N <= 20) {
        for(i=1; i <= 10; i++) {
            result = N * i;
            //cout << N << " x " << i << " = " << result << endl;
            printf("%d x %d = %d\n", N, i, result);
        }
    }

    return 0;
}


