//$ clang -Xclang -ast-dump -fsyntax-only result.c

struct www {
    float x,y,z;
};

struct xxx {
    struct www z;
    int yy;
    char c;
};

void f(void)
{
  struct xxx x;
}


