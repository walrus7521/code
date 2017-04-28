#include <stdio.h>

struct context;

struct funcptrs{
  void (*func0)(struct context *ctx);
  void (*func1)(void);
};

struct context{
    struct funcptrs fps;
}; 

void func1 (void) { printf( "1\n" ); }
void func0 (struct context *ctx) { printf( "0\n" ); }

void getContext(struct context *con){
    con->fps.func0 = func0;  
    con->fps.func1 = func1;  
}

int main(int argc, char *argv[]){
 struct context c;
   c.fps.func0 = func0;
   c.fps.func1 = func1;
   getContext(&c);
   c.fps.func0(&c);
   getchar();
   return 0;
}
