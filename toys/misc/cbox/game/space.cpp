#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;
 
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
 
void gameLoop()
{
    Player player;
    Bullet *bullet;
    movePlayer(player, 13, 10);
    while (!isLevelFinished() && player.lives > 0)
    {
        system("cls");
        showMap();
        showPlayer(player);
        if (GetAsyncKeyState(VK_SPACE))
        {
            if(!isBullet)
                bullet = new Bullet(player); isBullet = true;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayer(player, player.y, player.x-1);
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayer(player, player.y, player.x+1);
        }
        if (isBullet)
            if (!moveBullet(*bullet, player))
                delete bullet;
        Sleep(GameSpeed);
    }
    system("cls");
    cout << "Game Over!" << endl;
    cout << "Your final score was: " << player.score << endl;
}
 
 
int main()
{
    srand(time(0));
    gameLoop();
    cin.ignore();
    cin.get();
    return 0;
}

