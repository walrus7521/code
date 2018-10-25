#include <stdio.h>

// http://wiki.osdev.org/COFF
//

typedef struct _header {
    unsigned short  f_magic;    /* Magic number */	
    unsigned short  f_nscns;    /* Number of Sections */
    long        f_timdat;       /* Time & date stamp */
    long        f_symptr;       /* File pointer to Symbol Table */
    long        f_nsyms;        /* Number of Symbols */
    unsigned short  f_opthdr;   /* sizeof(Optional Header) */
    unsigned short  f_flags;    /* Flags */
} header;

void format_header(const unsigned char *buffer)
{
    header *hdr = (header *) buffer;
    printf("f_magic  : %x\n", hdr->f_magic);
    printf("f_nscns  : %x\n", hdr->f_nscns);
    printf("f_timdat : %x\n", hdr->f_timdat);
    printf("f_symptr : %x\n", hdr->f_symptr);
    printf("f_nsyms  : %x\n", hdr->f_nsyms);
    printf("f_opthdr : %x\n", hdr->f_opthdr);
    printf("f_flags  : %x\n", hdr->f_flags);

}

void hexdump(const unsigned char *buffer, unsigned long long length)
{
    char OffsetBuf[10];
    unsigned long long LastStart = 0, i, k, j;
    unsigned long long elf_bias = -62;

    format_header(buffer);

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

//int BUFFER_SIZE = 2000000;
int BUFFER_SIZE = 200;
FILE *source;
int n;
int count = 0;
int written = 0;

int main() {
    char buffer[BUFFER_SIZE];
    source = fopen("mem.out", "rb");
    if (source) {
        //while (!feof(source)) {
            n = fread(buffer, 1, BUFFER_SIZE, source);
            count += n;
            printf("n = %d\n", n);
            hexdump(buffer, n);
        //}
        printf("%d bytes read from library.\n", count);
    } else {
        printf("fail\n");
    }

    fclose(source);

    return 0;
}


