#include <stdio.h>

// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
//

typedef struct _int_t {
    union {
        unsigned char  b[2];
        unsigned short s;
    };
} Int_t;

typedef struct _long_t {
    union {
        unsigned char  b[4];
        unsigned short l;
    };
} Long_t;

typedef struct _longlong_t {
    union {
        unsigned char  b[8];
        unsigned short ll;
    };
} Longlong_t;

void format_header(const unsigned char *buffer)
{
    Int_t i;
    Long_t l;
    Longlong_t ll;
    unsigned long long entry, phtable, shtable;
    unsigned int index, e_flags, e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx;

    int is32bit = 0;

    printf("%c %c %c \n", buffer[1], buffer[2], buffer[3]);
    if (buffer[4] == 1) {
        printf("class : %s\n", "32-bit");
        is32bit = 1;
    } else {
        printf("class : %s\n", "64-bit");
        is32bit = 0;
    }
    printf("endian: %s\n", (buffer[5] == 1) ? "little" : "big");
    printf("version: %x\n", buffer[6]);
    switch (buffer[7]) {
        case 0x00: printf("System V\n"); break;
        case 0x01: printf("HP-UX\n"); break;
        case 0x02: printf("NetBSD\n"); break;
        case 0x03: printf("Linux\n"); break;
        case 0x06: printf("Solaris\n"); break;
        case 0x07: printf("AIX\n"); break;
        case 0x08: printf("IRIX\n"); break;
        case 0x09: printf("FreeBSD\n"); break;
        case 0x0C: printf("OpenBSD\n"); break;
        case 0x0D: printf("OpenVMS\n"); break;
        case 0x0E: printf("NSK operating system\n"); break;
        case 0x0F: printf("AROS\n"); break;
        case 0x10: printf("Fenix OS\n"); break;
        case 0x11: printf("CloudABI\n"); break;
        default: printf("unknown target OS %x\n", buffer[7]);
    }
    printf("ABI version: %x\n", buffer[8]);
    i.b[0] = buffer[0x10];
    i.b[1] = buffer[0x11];
    printf("Object type: %d\n", i.s);
    i.b[0] = buffer[0x12];
    i.b[1] = buffer[0x13];
    printf("Processor type: ");
    switch (i.s) {
        case 0x00: printf("No specific instruction set\n"); break;
        case 0x02: printf("SPARC\n"); break;
        case 0x03: printf("x86\n"); break;
        case 0x08: printf("MIPS\n"); break;
        case 0x14: printf("PowerPC\n"); break;
        case 0x28: printf("ARM\n"); break;
        case 0x2A: printf("SuperH\n"); break;
        case 0x32: printf("IA-64\n"); break;
        case 0x3E: printf("x86-64\n"); break;
        case 0xB7: printf("AArch64\n"); break;
        default:   printf("unknown %x\n", i.s); break;
    }
    l.b[0] = buffer[0x14];
    l.b[1] = buffer[0x15];
    l.b[2] = buffer[0x16];
    l.b[3] = buffer[0x17];
    printf("Version: %x\n", l.l);
    index = 0x18;
    if (is32bit) {
        l.b[0] = buffer[0x18];
        l.b[1] = buffer[0x19];
        l.b[2] = buffer[0x1a];
        l.b[3] = buffer[0x1b];        
        entry = l.l;
        l.b[0] = buffer[0x1c];
        l.b[1] = buffer[0x1d];
        l.b[2] = buffer[0x1e];
        l.b[3] = buffer[0x1f];        
        phtable = l.l;
        l.b[0] = buffer[0x20];
        l.b[1] = buffer[0x21];
        l.b[2] = buffer[0x22];
        l.b[3] = buffer[0x23];        
        shtable = l.l;
        index = 0x24;
    } else {
        ll.b[0] = buffer[0x18];
        ll.b[1] = buffer[0x19];
        ll.b[2] = buffer[0x1a];
        ll.b[3] = buffer[0x1b];
        ll.b[4] = buffer[0x1c];
        ll.b[5] = buffer[0x1d];
        ll.b[6] = buffer[0x1e];
        ll.b[7] = buffer[0x1f];
        entry = ll.ll;
        ll.b[0] = buffer[0x20];
        ll.b[1] = buffer[0x21];
        ll.b[2] = buffer[0x22];
        ll.b[3] = buffer[0x23];
        ll.b[4] = buffer[0x24];
        ll.b[5] = buffer[0x25];
        ll.b[6] = buffer[0x26];
        ll.b[7] = buffer[0x27];
        phtable = ll.ll;
        ll.b[0] = buffer[0x28];
        ll.b[1] = buffer[0x29];
        ll.b[2] = buffer[0x2a];
        ll.b[3] = buffer[0x2b];
        ll.b[4] = buffer[0x2c];
        ll.b[5] = buffer[0x2d];
        ll.b[6] = buffer[0x2e];
        ll.b[7] = buffer[0x2f];
        shtable = ll.ll;
        index = 0x30;
    }
    printf("Entry: %llx\n", entry);
    printf("PH table: %llx\n", phtable);
    printf("SH table: %llx\n", shtable);

    l.b[0] = buffer[index++];
    l.b[1] = buffer[index++];
    l.b[2] = buffer[index++];
    l.b[3] = buffer[index++];        
    e_flags = l.l;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_ehsize = i.s;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_phentsize = i.s;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_phnum = i.s;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_shentsize = i.s;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_shnum = i.s;
    i.b[0] = buffer[index++];
    i.b[1] = buffer[index++];
    e_shstrndx = i.s;
    printf("flags:      %04x\n", e_flags);
    printf("ehsize:     %02x\n", e_ehsize);
    printf("phentsize:  %02x\n", e_phentsize);
    printf("phnum:      %02x\n", e_phnum);
    printf("shentsize:  %02x\n", e_shentsize);
    printf("shnum:      %02x\n", e_shnum);
    printf("shstrndx:   %02x\n", e_shstrndx);

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
    source = fopen("start.elf", "rb");
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


