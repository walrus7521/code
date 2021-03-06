/* quest.c */

/*
 * gcc quest.c -lncurses -lpthread
 *
 *
 */

#include <curses.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define GRASS  	  ' '
#define EMPTY     '.'
#define WATER	  '~'
#define MOUNTAIN  '^'
#define PLAYER	  '*'

int is_move_okay(int y, int x);
void draw_map(void);

void do_one_thing(int *pnum_times) {
    int i, j, x;
    for (i = 0; i < 4; i++) {
        //printw("do one thing\n");
        for (j = 0; j < 10000; j++) {
            x += i;
        }
        (*pnum_times)++;
    }
}

void do_another_thing(int *pnum_times) {
    int i, j, x;
    for (i = 0; i < 4; i++) {
        //printw("do another thing\n");
        for (j = 0; j < 10000; j++) {
            x += i;
        }
        (*pnum_times)++;
    }
}

int r1, r2;

int main(void)
{
    int y, x;
    int ch;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, (void *) do_one_thing, (void *) &r1);
    pthread_create(&t2, NULL, (void *) do_another_thing, (void *) &r2);

    /* initialize curses */

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    clear();

    /* initialize the quest map */

    draw_map();

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printw("dude\n");


    /* start player at lower-left */

    y = LINES - 1;
    x = 0;

    do {
	/* by default, you get a blinking cursor - use it to indicate player */

	mvaddch(y, x, PLAYER);
	move(y, x);
	refresh();

	ch = getch();

	/* test inputted key and determine direction */

	switch (ch) {
	case KEY_UP:
	case 'w':
	case 'W':
	    if ((y > 0) && is_move_okay(y - 1, x)) {
		mvaddch(y, x, EMPTY);
		y = y - 1;
	    }
	    break;
	case KEY_DOWN:
	case 's':
	case 'S':
	    if ((y < LINES - 1) && is_move_okay(y + 1, x)) {
		mvaddch(y, x, EMPTY);
		y = y + 1;
	    }
	    break;
	case KEY_LEFT:
	case 'a':
	case 'A':
	    if ((x > 0) && is_move_okay(y, x - 1)) {
		mvaddch(y, x, EMPTY);
		x = x - 1;
	    }
	    break;
	case KEY_RIGHT:
	case 'd':
	case 'D':
	    if ((x < COLS - 1) && is_move_okay(y, x + 1)) {
		mvaddch(y, x, EMPTY);
		x = x + 1;
	    }
	    break;
	}
    }
    while ((ch != 'q') && (ch != 'Q'));

    endwin();

    exit(0);
}

int is_move_okay(int y, int x)
{
    int testch;

    /* return true if the space is okay to move into */

    testch = mvinch(y, x);
    return ((testch == GRASS) || (testch == EMPTY));
}

void draw_map(void)
{
    int y, x;

    /* draw the quest map */

    /* background */

    for (y = 0; y < LINES; y++) {
	mvhline(y, 0, GRASS, COLS);
    }

    /* mountains, and mountain path */

    for (x = COLS / 2; x < COLS * 3 / 4; x++) {
	mvvline(0, x, MOUNTAIN, LINES);
    }

    mvhline(LINES / 4, 0, GRASS, COLS);

    /* lake */

    for (y = 1; y < LINES / 2; y++) {
	mvhline(y, 1, WATER, COLS / 3);
    }
}

