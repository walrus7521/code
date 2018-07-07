#include <ncurses.h>

int main()
{
    initscr();

    addstr("goodbyt, cruel C");
    refresh();
    getch();

    endwin();
    return (0);
}
