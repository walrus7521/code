#include <stdio.h>

// Hex Dump In Many Programming Languages
// http://c2.com/cgi/wiki?HexDumpInManyProgrammingLanguages
//

void hexdump(const unsigned char *buffer, unsigned long long length)
{
    char OffsetBuf[10];
    unsigned long long LastStart = 0, i, k, j;
    unsigned long long elf_bias = -62;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%08x", i+elf_bias);
            printf("%4s:", OffsetBuf);
        }
        if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02x ", buffer[i]);
        if (i % 16 == 15 || i == length-1) {
            if (i == length-1) {
                for (k = i % 16 ; k < 15 ; k++) {
                     printf( "   " );
                     if (k % 4 == 3 && k % 16 != 0) {
                         printf(" ");
                     }
                }
            }
            printf("|");
            for (j = LastStart ; j <= i ; j++) {
                if (j % 4 == 0) {
                    printf(" ");
                }
                if (buffer[j] > 31 && buffer[j] < 127) {
                    printf("%c", buffer[j]);
                } else {
                    printf(".");
                }
            }
            if (i == length-1) {
                printf("\n");
                break;
            }
            printf("\n");
            LastStart += 16;
        }        
    }
}

int BUFFER_SIZE = 2000000;
FILE *source;
int n;
int count = 0;
int written = 0;

int main() {
    char buffer[BUFFER_SIZE];
    source = fopen("MCP.out", "rb");
    if (source) {
        while (!feof(source)) {
            n = fread(buffer, 1, BUFFER_SIZE, source);
            count += n;
            printf("n = %d\n", n);
            hexdump(buffer, n);
        }
        printf("%d bytes read from library.\n", count);
    } else {
        printf("fail\n");
    }

    fclose(source);

    return 0;
}


