#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t completed_steps;
    size_t total_steps;
    char name[8];
} progress_bar;

void show_progress(progress_bar *bar)
{
    int i; 
    printf("dude: ");
    for (i = 0; i < bar->completed_steps; i++) {
        printf("-");
    }
    printf("\r");
}

int main()
{
    int i;
    progress_bar bar;
    strcpy(bar.name, "dude");
    bar.total_steps = 32;
    bar.completed_steps = 0;

    for (i = 0; i < 32; i++) {
        bar.completed_steps = i;
        show_progress(&bar);
        getchar();
    }

}

