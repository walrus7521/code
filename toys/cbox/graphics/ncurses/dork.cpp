#include <ncurses.h>
#include <unistd.h>
#include <vector>

// g++ dork.cpp -lcurses


using namespace std;

typedef struct{short int x, y, c; bool movhor, movver;} object;

int main() 
{
  object scr; int i = 0,cont=0; bool end=false;
  initscr();
  start_color();

  init_pair(1,COLOR_YELLOW, COLOR_BLACK);
  init_pair(2,COLOR_RED, COLOR_BLACK);

  keypad(stdscr,true);
  noecho();
  curs_set(0);
  getmaxyx(stdscr,scr.y,scr.x);

  object paddle_right = {scr.x-2,scr.y/2,0,false,false};
  object paddle_left  = {1,scr.y/2,0,false,false};
  object ball         = {scr.x/2,scr.y/2,0,false,false};

  mvprintw(4,0,"\t           oooooooooo                     o88   88o          \n"
               "\t           888    888  ooooooo  o8888888  888 88o            \n"
               "\t           888    88 888     888 888   8  888o               \n"
               "\t           888    88 888     888 888      888 88o            \n"
               "\t          o888o88888   88ooo88   oooo     8o8  888o          \n"
               "\t                                                             \n\n"
               "\t Any questions please send me at biteme@gmail.com            \n"
               "\t \t\t\tPlayer 1 your controls are 'a' and 'q'                \n"
               "\t \t\t\tPlayer 2 your controls are the arrows of the keyboard \n"
               "\t \t\t\tPush ANY key to start, 'p' for pause and ESC to quit" ); 
  getch();

  for (nodelay(stdscr,1); !end; usleep(4000)) {
    //beep();
    //flash();      
    if (++cont%16==0){
      if ((ball.y==scr.y-1)||(ball.y==1))
        ball.movver=!ball.movver;
      if ((ball.x>=scr.x-2)||(ball.x<=2)){
        ball.movhor=!ball.movhor;
        if ((ball.y==paddle_right.y-1)||(ball.y==paddle_left.y-1)) {
          ball.movver=false;
        } else if ((ball.y==paddle_right.y+1)||(ball.y==paddle_left.y+1)) {
          ball.movver=true;
        } else if ((ball.y != paddle_right.y) && (ball.y != paddle_left.y)) {
          (ball.x>=scr.x-2) ? paddle_right.c++: paddle_left.c++;
          ball.x=scr.x/2;
          ball.y=scr.y/2;
        }
      }

      ball.x = ball.movhor ? ball.x+1 : ball.x-1;
      ball.y = ball.movver ? ball.y+1 : ball.y-1;

      if (paddle_right.y <= 1)        paddle_right.y=scr.y-2;
      if (paddle_right.y >= scr.y-1)  paddle_right.y=2;
      if (paddle_left.y  <= 1)        paddle_left.y=scr.y-2;
      if (paddle_left.y  >= scr.y-1)  paddle_left.y=2;

    }

    /* user input */
    switch (getch()) {
      case KEY_DOWN: paddle_right.y++; break;
      case KEY_UP:   paddle_right.y--; break;
      case 'q':      paddle_left.y--; break;
      case 'a':      paddle_left.y++; break;
      case 'p':      getchar(); break;
      case 0x1B:    endwin(); end++; break; // ESC key
    }

    erase();

    mvprintw(2,scr.x/2-2,"%i | %i",paddle_right.c,paddle_left.c);
    mvvline(0,scr.x/2,ACS_VLINE,scr.y);
    
    attron(COLOR_PAIR(1));
    mvprintw(ball.y,ball.x,"o");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for(i=-1;i<2;i++){
        mvprintw(paddle_right.y+i,paddle_right.x,"|");
        mvprintw(paddle_left.y+i,paddle_left.x,"|");
    }
    attroff(COLOR_PAIR(2));
  }
}

