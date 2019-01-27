#include <stdio.h>
#include <unistd.h>

int main() {
    int i;

    // Disable output buffering.
    setbuf(stdout, NULL);

    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
        usleep(500000);
    }

    return 0;
}

