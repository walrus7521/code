#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
struct file_header {
    uint32_t recordsize;
    uint32_t numrecords;
};

struct book_record {
    char title[80];
    char author_last[20];
    char author_first[20];
    char publisher[40];
    uint32_t year;
};

static struct book_record mybooks[] = 
{
    {"c programming", "ritchie", "brian", "penn", 1987},
    {"programming pearls", "bentley", "jon", "add", 1992},
    {"data structs", "kruse", "bob", "pren", 1994}
};

static size_t numbooks = sizeof(mybooks)/sizeof(struct book_record);

static struct file_header myheader =
{
    sizeof(struct book_record),
    sizeof(mybooks)/sizeof(struct book_record)
};

void my_err(char *msg, int code)
{
    fprintf(stderr, "%s\n", msg);
    exit(code);
}

int main()
{
    FILE *dbfile;
    int c, file_open = 0;
    size_t numread, s_len, len;
    long fpos;
    char dbname[80], bktitle[80];
    struct book_record book;

    printf("database program\n");

    // create a database file
    printf("enter dbase name to create: ");
    gets(dbname);
    if ((dbfile = fopen(dbname, "wb+")) == NULL) {
        my_err("no such file", 1);
    }

    // turn off buffering
    setvbuf(dbfile, NULL, _IONBF, 0);
    
    // save header and book records
    if (fwrite(&myheader, sizeof(struct file_header), 1, dbfile) != 1) {
        my_err("write error", 2);
    }

    if (fwrite(mybooks, sizeof(struct book_record), numbooks, dbfile) != numbooks) {
        my_err("write error", 2);
    }
            
    // now let the user manipulate the databse
    while (1) {
next_cmd:
        printf("enter command\n"
                "(f = find a record, "
                " q = quit): ");

        while ((c = getchar()) != EOF) {
            getchar();
            fflush(stdin);
            switch (c) {
                case 'f':
                case 'F':
                    printf("title: ");
                    fgets(bktitle, 80, stdin);
                    //printf("%s\n", bktitle);
                    s_len = strlen(bktitle);
                    // set pointer to just after the header from the beginning
                    fseek(dbfile, (long) sizeof(struct file_header), SEEK_SET);
                    // find record with this title
                    do {
                        fpos = ftell(dbfile);
                        numread = fread(&book, sizeof(struct book_record), 1, dbfile);
                        len = strlen(book.title);
                        len = min(s_len, len);
                    } while (numread == 1 &&
                            strncmp(book.title, bktitle, len) != 0);
                    if (numread != 1) {
                        my_err("not found", 3);
                    }
                    printf("found: %s", book.title);
                    break;
                case 'q':
                case 'Q':
                    printf("exiting...\n");
                    fclose(dbfile);
                    exit(0);
                    break;
            }
        }
    }
}

