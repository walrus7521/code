#include <stdio.h>

// from Pearls 3.2 Form-Letter Programming

char fields[32][32] = {
                        "Public", "Jane", "Q", "Ms.", 
                        "600", "Maple Street", 
                        "Your Town", "Iowa", "12345"
                      };

char schema[] = 
"Welcome back,$1! \n\
We hope that you and all the members \n\
of the $0 family are constantly \n\
reminding your neighbors there \n\
on $5 to shop with us. \n\
As usual, we will ship your order to: \n\
$3 $1 $2. $0 \n\
$4 $5 \n\
$6 $7 $8\0";

int main()
{
    for (int i = 0; i < 9; i++) {
        printf("field[%d] = %s\n", i, fields[i]);
    }
    char c;
    int i;
    char *pschema = schema;
    while ((c = *pschema++) != '\0') {
        if (c != '$') {
            printf("%c", c);
        } else {
            c = *pschema++;
            switch (c) {
                case '$': putchar('$'); break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                          {
                          int idx = c - '0';
                          printf("%s", fields[idx]);
                          }
                          break;
                default: printf("bad schema\n"); break;

            }
        }
    }
    printf("\n");
}
