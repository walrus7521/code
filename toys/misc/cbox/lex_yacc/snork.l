%{
// http://aquamentus.com/flex_bison.html
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
%}
%{
    int linenum = 0;

    void write(const char *file_name, void *data, int len)
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

    void doit()
    {
        struct _object o;
        o.member1 = 42;
        o.member2 = 43;
        o.member3 = 44;
        o.member4 = 45;
        const char *filename = "test.bin";
        write(filename, (void *) &o, sizeof(struct _object));
        struct _object o2;
        read(filename, (void *) &o2, sizeof(struct _object));
        show(&o2);
    }

    void init()
    {
        cout << "sup dawg\n";
    }
    
%}
%%
[ \t]           ;
[ \n]           { linenum++; }
douche          { cout << "bag\n"; doit(); }
quit            { return 0; }
[0-9]+\.[0-9]+  { cout << linenum << "] " << "Found a floating-point number:" << yytext << endl; }
[0-9]+          { cout << linenum << "] " << "Found an integer:" << yytext << endl; }
[a-zA-Z0-9]+    { cout << linenum << "] " << "Found a string: " << yytext << endl; }
%%
int main(int, char**) {
	// lex through the input:
    init();
	yylex();
}

