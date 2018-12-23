#include<stdio.h>

// https://www.codingunit.com/c-tutorial-binary-file-io

/* Our structure */
struct rec
{
    int x,y,z;
};

int write_bin()
{
    int counter;
    FILE *ptr_myfile;
    struct rec my_record;

    ptr_myfile=fopen("test.bin","wb");
    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    for ( counter=1; counter <= 10; counter++)
    {
        my_record.x= counter-1;
        my_record.y= counter;
        my_record.z= counter+1;
        fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
    }
    fclose(ptr_myfile);
    return 0;
}

int read_bin()
{
    int counter;
    FILE *ptr_myfile;
    struct rec my_record;

    ptr_myfile=fopen("test.bin","rb");
    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        return 1;
    }
    for ( counter=1; counter <= 10; counter++)
    {
        fread(&my_record,sizeof(struct rec),1,ptr_myfile);
        printf("%d\n",my_record.x);
    }
    fclose(ptr_myfile);
    return 0;
}

int main()
{
    write_bin();
    read_bin();
}

