#include <stdio.h>
#include <windows.h>
#include "windll.h"

int main(void)
{
    hello("World");
    printf("%d\n", Double(333));
    CppFunc();

    MyClass a;
    a.func();
    CreateWin(NULL, NULL, (LPSTR) L"dude", 1);
    CreateWin(NULL, NULL, (LPSTR) L"dude", 1);

    return 0;
}
