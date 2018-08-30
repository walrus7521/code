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
    int i;
    int *st1 = pin[0];
    int *st2 = pin[1];
    int *st3 = pin[2];
    printf("pin1: ");
    for (i = 0; i < sp1; i++) {
        printf("%d - ", st1[i]);
    }
    printf("\n");
    printf("pin2: ");
    for (i = 0; i < sp2; i++) {
        printf("%d - ", st2[i]);
    }
    printf("\n");
    printf("pin3: ");
    for (i = 0; i < sp3; i++) {
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

//int moves = 0;

void move_nr(int moves)
{
    int x;
    int *st1 = pin[0];
    int *st2 = pin[1];
    int *st3 = pin[2];

    // establish a sequence: 
    //      1 <-?-> 2
    //      1 <-?-> 3
    //      2 <-?-> 3

    if (moves & 0x001) {
        x = pop(st1, &sp1);
        push(st2, &sp2, x);
    } else {
        x = pop(st2, &sp2);
        push(st1, &sp1, x);
    }

    if (moves & 0x010) {
        x = pop(st1, &sp1);
        push(st3, &sp3, x);
    } else {
        x = pop(st3, &sp3);
        push(st1, &sp1, x);
    }

    if (moves & 0x100) {
        x = pop(st2, &sp2);
        push(st3, &sp3, x);
    } else {
        x = pop(st3, &sp3);
        push(st2, &sp2, x);
    }
    show();
}

/*
 * A <-> B: A even A -> B
 * A <-> C: 
 * B <-> C: 
 */
int main()
{
    printf("A->B\n");
    printf("A->C\n");
    printf("B->C\n");

    pin[0] = stack1;
    pin[1] = stack2;
    pin[2] = stack3;

    push(stack1, &sp1, 8);
    push(stack1, &sp1, 4);
    push(stack1, &sp1, 2);
    push(stack1, &sp1, 1);

    show();
    move_nr(0x111);
    move_nr(0x001);
    move_nr(0x111);
    move_nr(0x100);
    move_nr(0x111);

}
