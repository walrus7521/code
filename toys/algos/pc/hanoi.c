#include <stdio.h>
#include <stdint.h>

int *pin[3];
int stack1[4] = {0};
int stack2[4] = {0};
int stack3[4] = {0};
int sp1 = 0;
int sp2 = 0;
int sp3 = 0;

void show()
{
    int *st1 = pin[0];
    int *st2 = pin[1];
    int *st3 = pin[2];
    printf("pin1: ");
    for (int i = 0; i < sp1; i++) {
        printf("%d - ", st1[i]);
    }
    printf("\n");
    printf("pin2: ");
    for (int i = 0; i < sp2; i++) {
        printf("%d - ", st2[i]);
    }
    printf("\n");
    printf("pin3: ");
    for (int i = 0; i < sp3; i++) {
        printf("%d - ", st3[i]);
    }
    printf("\n");
}

int pop(int *s, int *i)
{
    (*i)--;
    int v = s[*i];
    return v;
}

void push(int *s, int *i, int v)
{
    s[*i] = v;
    (*i)++;
}

void move()
{
    int x;
    int *st1 = pin[0];
    int *st2 = pin[1];
    int *st3 = pin[2];

    // establish a sequence: 
    //      1 <-?-> 2
    //      1 <-?-> 3
    //      2 <-?-> 3

    x = pop(st1, &sp1);
    push(st2, &sp2, x);
    x = pop(st1, &sp1);
    push(st3, &sp3, x);
    x = pop(st2, &sp2);
    push(st3, &sp3, x);
}

/*
 * A <-> B: A even A -> B
 * A <-> C: 
 * B <-> C: 
 */
int main()
{
    pin[0] = stack1;
    pin[1] = stack2;
    pin[2] = stack3;

    push(stack1, &sp1, 8);
    push(stack1, &sp1, 4);
    push(stack1, &sp1, 2);
    push(stack1, &sp1, 1);

    show();
    move();
    show();
}
