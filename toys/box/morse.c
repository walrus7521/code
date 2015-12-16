#include <stdio.h>
#include <string.h>


struct letter {
  int n;
  char a[8];
};

struct letter alphabet[26] = {
  {2, {'.','-'}},               // a
  {4, {'-','.','.','.'}},       // b
  {4, {'-','.','-','.'}},       // c
  {3, {'-','.','-','.'}},       // d
  {1, {'.'}},                   // e
  {4, {'.','.','-','.'}},       // f
  {3, {'-','-','.'}},           // g
  {4, {'.','.','.','.'}},       // h

};

void dot()
{
    printf(".");
}

void dash()
{
    printf("-");
}

void letter(char a)
{
    int i;
    int idx = a-'a';
    struct letter l = alphabet[idx];
    printf("%c: ", a);
    for (i = 0; i < l.n; ++i) {
        if (l.a[i] == '.') dot();
        else dash();
    }
    printf("\n");
}

int main()
{
    char str[] = "abcdefgh";
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++) {
        letter(str[i]);
    }
}
