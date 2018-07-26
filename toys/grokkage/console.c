#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

enum {
    BLACK        = 0,
    BLUE         = 1,
    GREEN        = 2,
    AQUA         = 3,
    RED          = 4,
    PURPLE       = 5,
    YELLOW       = 6,
    WHITE        = 7,
    GRAY         = 8,
    LIGHT_BLUE   = 9,
    LIGHT_GREEN  = 10,
    LIGHT_AQUA   = 11,
    LIGHT_RED    = 12,
    LIGHT_PURPLE = 13,
    LIGHT_YELLOW = 14,
    LIGHT_WHITE  = 15,
  
    DEFAULT      = 16
};

static WORD defaults;
static int defaults_loaded = 0;

static void pt_color(int color)
{ 
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!defaults_loaded) {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(console, &info);
        defaults = info.wAttributes;
        defaults_loaded = 1;
    }
    SetConsoleTextAttribute(console, color == DEFAULT ? defaults : color);
}

#else

static const char* colors[] = {
  "\x1B[0m",
  "\x1B[34m",
  "\x1B[32m",
  "\x1B[36m",
  "\x1B[31m",
  "\x1B[35m",
  "\x1B[33m",
  "\x1B[37m",
  "",
  "\x1B[34m",
  "\x1B[32m",
  "\x1B[36m",
  "\x1B[31m",
  "\x1B[35m",
  "\x1B[33m",
  "\x1B[37m",
  "\x1B[39m",
};

static void pt_color(int color) {  
  printf("%s", colors[color]);
}

#endif


int num_tests = 42;

void run()
{
    puts("");
    puts("    +-------------------------------------------+");
    puts("    |              C console                    |");
    puts("    |                                           |");
    puts("    | http://github.com/walrus7521              |");
    puts("    |                                           |");
    puts("    | Bart Bartel (bartb7@gmail.com)            |");
    puts("    +-------------------------------------------+");
    puts("");
    puts("  +---------------------------------------------------+");
    puts("  |                      Summary                      |");
    puts("  +---------++------------+-------------+-------------+");
  
    printf("  | Suites  ||");
    pt_color(YELLOW);  printf(" Total %4d ",  num_tests);        
    pt_color(DEFAULT); putchar('|');
    pt_color(GREEN);   printf(" Passed %4d ", num_tests); 
    pt_color(DEFAULT); putchar('|');
    pt_color(RED);     printf(" Failed %4d ", num_tests);  
    pt_color(DEFAULT); puts("|");
  
    printf("  | Tests   ||");
    pt_color(YELLOW);  printf(" Total %4d ",  num_tests);         
    pt_color(DEFAULT); putchar('|');
    pt_color(GREEN);   printf(" Passed %4d ", num_tests);  
    pt_color(DEFAULT); putchar('|');
    pt_color(RED);     printf(" Failed %4d ", num_tests);   
    pt_color(DEFAULT); puts("|");
  
    printf("  | Asserts ||");
    pt_color(YELLOW);  printf(" Total %4d ",  num_tests);       
    pt_color(DEFAULT); putchar('|');
    pt_color(GREEN);   printf(" Passed %4d ", num_tests); 
    pt_color(DEFAULT); putchar('|');
    pt_color(RED);     printf(" Failed %4d ", num_tests);  
    pt_color(DEFAULT); puts("|");
  
    puts("  +---------++------------+-------------+-------------+");
    puts("");
  
}

int main()
{
    run();
}

