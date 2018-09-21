#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int task_queue[256] = {INT_MAX};
int task_queue_size = 0;

void Task_Show() {
    int i;
    for (i = 1; i <= task_queue_size; i++) printf("%02d, ", task_queue[i]);
    printf("\n");
}

void Task_Down(int k) {
    int child, last = task_queue[k]; /* grab min */
    while (k <= task_queue_size/2) {
        child = 2 * k;
        if (child < task_queue_size && task_queue[child+1] < task_queue[child]) child++;
        if (last <= task_queue[child]) break;
        task_queue[k] = task_queue[child];
        k = child;
    }
    task_queue[k] = last;
}

void Task_Up(int k) {
    int v = task_queue[k];
    while (task_queue[k/2] > v) {
        task_queue[k] = task_queue[k/2];
        k = k/2;
    }
    task_queue[k] = v;
}

int Task_Decrement_Keys(int amt)
{
    int i;
    for (i = 1; i <= task_queue_size; i++) task_queue[i] -= amt;
}

int main()
{
    int a[] = { 34, 5, 23, 12, 33, 98, 4, 13, 44, 37, 1, 86, 8};
    int i, len=sizeof(a) / sizeof(a[0]);

    printf("min heap\n");
    task_queue_size = 0;
    task_queue[0] = -INT_MAX;
    for (i = 0; i < len; i++) {
        task_queue[++task_queue_size] = a[i]; // insert at bottom
        Task_Up(task_queue_size); // bubble up
    }
    Task_Show();
    while (task_queue_size != 0) {
        int min = task_queue[1]; // save top
        task_queue[1] = task_queue[task_queue_size--]; // copy bottom to top
        Task_Down(1); // sink down
        printf("%02d : ", min);
        Task_Show();
        Task_Decrement_Keys(min);
    }

}

