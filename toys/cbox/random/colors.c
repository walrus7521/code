#if 0
#include <stdio.h>

// http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// https://stackoverflow.com/questions/2048509/how-to-echo-with-different-colors-in-the-windows-command-line
//

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define HILI "[101;93m STYLES [0m"

int main (int argc, char const *argv[]) 
{
    printf(HILI);
    printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");

}
#endif

#include <stdio.h>
#include <windows.h>

int main(void)
{   
    /* Point to our console */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i = 0;
#if 0
    /* Iterate through colors */ 
    for(; i < 255; i++)
    { /* i stands for color type: could refer to actual text color or background color of text */
        SetConsoleTextAttribute(hConsole, i);
        printf("Colorful text");
    }
#endif
    SetConsoleTextAttribute(hConsole, 31);
    printf("dude, wusup\n");
    SetConsoleTextAttribute(hConsole, 32);
    printf("oh, namuch\n");
//    SetConsoleTextAttribute(hConsole, 0);
//
    CloseHandle(hConsole);

    getchar();
    return 0;
}
