#include <string>
#include <curses.h>
using namespace std;

// g++ -lncurses pass.cpp 

string getpass(const char *prompt)
{
  printw(prompt);
  noecho();  // disable character echoing

  char buff[64];
  getnstr(buff,sizeof(buff));

  echo(); // enable character echoing again
  return buff;
}

int main()
{
   const string correct_password="null";

   initscr(); // enable ncurses

   string pwd=getpass("Please enter the password: ");

   if(correct_password==pwd)
       printw("\nCorrect password!");
   else
       printw("\nIncorrect password. Try again");


    getch(); // Wait for a keypress
    endwin(); // disable ncurses

    return 0;
}
