#include <ncurses.h>

#define PINK (1)

int main()
{
    initscr();
    if (!has_colors()) {
        endwin();
        puts("Terminal cannot do colors");
        return (1);
    }
    if (!can_change_color()) {
        addstr("this probably won't work");
    }
    init_color(PINK, 1000, 750, 750);
    init_pair(1, PINK, COLOR_BLACK);
    attrset(COLOR_PAIR(1));
    printw("This is the new color %d\n", PINK);
    refresh();

    if (start_color() != OK) {
        endwin();
        puts("Unable to start colors");
        return (1);
    }
    printw("Colors initialized.\n");
    printw("%d colors available\n", COLORS);
    printw("%d color pairs", COLOR_PAIRS);

    init_pair(1, COLOR_YELLOW, COLOR_RED);
    addstr("Normal text\n");
    attrset(COLOR_PAIR(1));
    addstr("Colored text\n");
    attrset(A_NORMAL);
    addstr("Back to normal.");
    refresh();

    int i;
    for (i = 0; i < COLORS; i++) {
        init_pair(i, i, 256-i);
        attrset(COLOR_PAIR(i));
        addstr("x");
        refresh();
    }

    getch();
    endwin();
    return (0);
}
