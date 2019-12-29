#include <stdio.h>
#include <mach-o/loader.h>

// Hex Dump In Many Programming Languages
// http://c2.com/cgi/wiki?HexDumpInManyProgrammingLanguages
// https://opensource.apple.com/source/xnu/xnu-792/EXTERNAL_HEADERS/mach-o/loader.h
// https://www.mikeash.com/pyblog/friday-qa-2012-11-30-lets-build-a-mach-o-executable.html
// http://hackage.haskell.org/package/macho-0.22/docs/src/Data-Macho.html
//
//

void hexdump(const unsigned char *buffer, unsigned long long length)
{
    char OffsetBuf[10];
    unsigned long long LastStart = 0, i, k, j;
    unsigned long long elf_bias = -62;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%08llx", i);
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

void dump_header(char *buffer)
{
    struct mach_header *hdr = (struct mach_header *) buffer;
    printf("magic: %08x\n", hdr->magic);
    switch (hdr->cputype) {
        case CPU_TYPE_X86:    printf("CPU_TYPE_X86\n"); break;
        case CPU_TYPE_X86_64: printf("CPU_TYPE_X86_64\n"); break;
        case CPU_TYPE_ARM:    printf("CPU_TYPE_ARM\n"); break;
    }
}


int BUFFER_SIZE = 2000000;
FILE *source;
int n;
int count = 0;
int written = 0;

int main() {
    char buffer[BUFFER_SIZE];
    source = fopen("test.bin", "rb");
    if (source) {
        while (!feof(source)) {
            n = fread(buffer, 1, BUFFER_SIZE, source);
            count += n;
            printf("n = %d\n", n);
            //hexdump((const unsigned char *) buffer, n);
        }
        printf("%d bytes read from library.\n", count);
    } else {
        printf("fail\n");
    }

    dump_header(buffer);

    fclose(source);

    return 0;
}


