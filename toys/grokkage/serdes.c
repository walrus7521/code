#include <stdio.h>
#include <stdlib.h>

//void write(char *file_name, struct _object *data)
void write(char *file_name, void *data, int len)
{
    FILE *f;
    f = fopen(file_name,"wb");
    if (!f) {
        printf("Unable to open file!");
        return;
    }
    //fwrite(data, sizeof(struct _object), 1, f);    
    fwrite(data, len, 1, f);    
    fclose(f);
};

//void read(const char *file_name, struct _object *data)
void read(const char *file_name, void *data, int len)
{
    FILE *f;
    f = fopen(file_name,"rb");
    if (!f) {
        printf("Unable to open file!");
        return;
    }
    //fread(data, sizeof(struct _object), 1, f);    
    fread(data, len, 1, f);    
    fclose(f);
}

struct _object {
    int member1;
    int member2;
    int member3;
    int member4;
};

void show(struct _object *data)
{
    printf("%d\n", data->member1);
    printf("%d\n", data->member2);
    printf("%d\n", data->member3);
    printf("%d\n", data->member4);
}

int main()
{
    struct _object o;
    o.member1 = 42;
    o.member2 = 43;
    o.member3 = 44;
    o.member4 = 45;
    write("test.bin", (void *) &o, sizeof(struct _object));
    struct _object o2;
    read("test.bin", (void *) &o2, sizeof(struct _object));
    show(&o2);
}

