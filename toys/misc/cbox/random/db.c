#include <stdio.h>
#include <stdlib.h>


// https://www.codingunit.com/c-tutorial-binary-file-io
// TODO:
//  create an index file off account number and offset
//  on opening database, have option to rescan to update index file
// Flow:
//    when accessing an account:
//        1. scan index file for existence
//        2. if exists, update and rewrite
//        3. if not exists,
//            a. create new account
//            b. allocate new index and file offset
//            c. write new account record to file


struct meta
{
    int n_recs;
    int date;
};

struct rec
{
    int x,y,z;
    int offset;
    char name[8];
};

void dump(FILE *dbfile, int nrecs)
{
    int i;
    struct rec my_record;

    fseek(dbfile, sizeof(struct meta), SEEK_SET);
    for (i = 0; i < nrecs; i++) {
        fread(&my_record, sizeof(struct rec), 1, dbfile);
        printf("%03d %c %02x %04x %s\n", 
                my_record.x, 
                my_record.y, 
                my_record.z, 
                my_record.offset,
                my_record.name);
    }
}

void add_record(FILE *dbfile, struct rec *r)
{
    fseek(dbfile, 0, SEEK_END);
    r->offset = ftell(dbfile);
    fwrite(r, sizeof(struct rec), 1, dbfile);
}

int main()
{
    FILE *dbfile;
    int counter;
    struct rec my_record;
    struct meta meta;

    dbfile = fopen("test.img","rb+");
    if (!dbfile) {
        printf("Unable to open file!");
        return 1;
    }

    fseek(dbfile, 0, SEEK_SET);
    fread(&meta, sizeof(struct meta), 1, dbfile);
    printf("record size: %ld, num %d, date %x\n", 
            sizeof(struct rec), meta.n_recs, meta.date);
    fseek(dbfile, sizeof(struct meta), SEEK_SET);

#if 0
    my_record.x = 22;
    my_record.y = 'z';
    my_record.z = 0x43;
    sprintf(my_record.name, "%s-%02d", "bart", 45);
    add_record(dbfile, &my_record);
#endif

#if 0
    for (counter=1; counter <= 20; counter++) {
        my_record.x= counter;
        my_record.y = 'a' + counter - 1;
        my_record.z = 0x41 + counter;
        my_record.offset = ftell(dbfile);
        sprintf(my_record.name, "%s-%02d", "bart", counter);
        fwrite(&my_record, sizeof(struct rec), 1, dbfile);
    }
#endif

    fflush(dbfile);
    dump(dbfile, meta.n_recs);

    fseek(dbfile, 0, SEEK_SET);
    fread(&meta, sizeof(struct meta), 1, dbfile);
    fseek(dbfile, 0, SEEK_SET);
    //meta.n_recs = meta.n_recs+1;//counter;
    meta.date = 0x42;
    fwrite(&meta, sizeof(struct meta), 1, dbfile);
    fflush(dbfile);

    fclose(dbfile);
    return 0;
}


