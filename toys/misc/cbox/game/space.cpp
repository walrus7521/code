#include <iostream>
#include <ctime>
#include <unistd.h>
#include <thread>
//#include <Windows.h>
using namespace std;
 
#define KEY_BULLET  (0)
#define KEY_LEFT    (1)
#define KEY_RIGHT   (2)
#define KEY_QUIT    (3)
#define KEY_HELP    (4)
#define KEY_INVALID (42)

const char SYMBOL_EMPTY = ' ';
const char SYMBOL_PLAYER = '^';
const char SYMBOL_ALIEN = 'A';
const char SYMBOL_WALL = '#';
const char SYMBOL_BULLET = '*';
const int MapDy = 15;
const int GameSpeed = 1000;
bool isBullet = false;
 
struct Player
{
    int x, y, startx, starty, score, lives;
    Player()
    {
        x = -1;
        y = -1;
        starty = 13;
        startx = 10;
        score = 0;
        lives = 3;
    }
};
 
struct Bullet
{
    int x, y;
    Bullet(Player &player)
    {
        x = player.x;
        y = player.y;
        printf("bullet: x:%d y:%d\n", x, y);
    }
};
 
char board[15][20] =
{
    "###################",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "###################"
};
 
bool isValidPos(int x, int y)
{
    return (x >= 0 && x < 20 && y >= 0 && y < 15);
}
 
bool moveBullet(Bullet &bullet, Player &player)
{
    printf("bullet: x:%d, y:%d\n", bullet.x, bullet.y);
    if(isValidPos(bullet.x, bullet.y+1))
    {
        char ch = board[bullet.y+1][bullet.x];
        if (ch == SYMBOL_EMPTY)
        {
            board[bullet.y][bullet.x] = SYMBOL_EMPTY;
            bullet.y++;
            board[bullet.y][bullet.x] = SYMBOL_BULLET;
            return true;
        }
        else if (ch == SYMBOL_ALIEN)
        {
            board[bullet.y][bullet.x] = SYMBOL_EMPTY;
            board[bullet.y+1][bullet.x] = SYMBOL_EMPTY;
        }
        else
        {
            board[bullet.y][bullet.x] = SYMBOL_EMPTY;
        }
    }
    return false;
}
 
void movePlayer(Player &player, int y, int x)
{
    printf("move: x:%d y:%d\n", x, y);
    if (!isValidPos(x, y))
    {
        return;
    }
     
    char ch = board[y][x];
 
    if(ch != SYMBOL_EMPTY)
    {
        return;
    }
     
    if (isValidPos(player.x, player.y))
    {
        board[player.y][player.x] = SYMBOL_EMPTY;
    }
    player.y = y; player.x = x;
    board[player.y][player.x] = SYMBOL_PLAYER;
    return;
}
 
bool isLevelFinished()
{
    return false;
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            if (board[y][x] == SYMBOL_ALIEN)
            {
                return false;
            }
        }
    }
    return true;
}
 
void showPlayer(Player &player)
{
    cout << "\nPlayerX: " << player.x << endl;
    cout << "PlayerY: " << player.y << endl;
    cout << "Player's Score: " << player.score << endl;
    cout << "Player's Lives: " << player.lives << endl;
}
 
void showMap()
{
    for (int y = 0; y < MapDy; y++)
    {
        cout << board[y] << endl;
    }
}
 
void usage()
{
    printf("h: help\n");
    printf("b: bullet\n");
    printf("r: right\n");
    printf("l: left\n");
    printf("q: quit\n");
}

int getInput()
{
    char c = ' ';
retry:
    printf("> ");
    c = getchar();
    //printf("got: %x\n", c);
    switch (c) {
        case 'h': usage();            return KEY_HELP;
        case 'b': printf("bullet\n"); return KEY_BULLET;
        case 'l': printf("left\n");   return KEY_LEFT;
        case 'r': printf("right\n");  return KEY_RIGHT;
        case 'q': printf("quit\n");   return KEY_QUIT;
    }
    printf("\r");
    goto retry;
}

void gameLoop()
{
    Player player;
    Bullet *bullet;
    movePlayer(player, 13, 10);
    int input;
    while (!isLevelFinished() && player.lives > 0)
    {
        //system("cls");
        system("\033[2J");
        movePlayer(player, player.y, player.x);
        if (isBullet) moveBullet(*bullet, player);
        showMap();
        showPlayer(player);
        input = getInput();
        switch (input) {
            case KEY_BULLET:
                if(!isBullet) {
                    bullet = new Bullet(player); 
                    isBullet = true;
                }
                break;
            case KEY_LEFT:
                movePlayer(player, player.y, player.x-1);
                break;
            case KEY_RIGHT:
                movePlayer(player, player.y, player.x+1);
                break;
            case KEY_HELP:
            case KEY_INVALID:
                break;
            case KEY_QUIT:
                goto exit;
        }
        if (isBullet) {
            if (!moveBullet(*bullet, player)) {
                delete bullet;
                isBullet = false;
            }
        }
        //Sleep(GameSpeed);
        //sleep(1);
    }
exit:
    //system("cls");
    cout << "Game Over!" << endl;
    cout << "Your final score was: " << player.score << endl;
}
 
#include <pthread.h>
#include <iostream>

using std::cout;

void bullets()
{
    while (1) {
        cout << ".";
        sleep(1);
    }
}

int main()
{
    void *status;
    pthread_t id;
    std::thread t(bullets);
    //if (pthread_join(id, &status)) {
    //    pthread_cancel(id);
    //    return 0;
    //}


    srand(time(0));
    gameLoop();
    return 0;
}

