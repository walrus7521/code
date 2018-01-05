#include <stdio.h>
#include <stdbool.h>

bool                 g_keepPlaying = false;
bool                 g_update = false;
int                  g_frame = 0;

void GetInput();
void UpdateWorld();

void Init()
{
    g_keepPlaying = true;
}

void UnInit()
{
}

void PlayGame() 
{
    while (g_keepPlaying) {
        GetInput();
        if (g_update) {
            UpdateWorld();
        }
    }
}
 
void MainMenu() 
{
    // display menu
    // get option
    //if (option == PLAY_THE_GAME)
    PlayGame();
    // etc.
}

// simulate joystick here
void GetInput()
{
    char c = getchar();
    if (c == 'q') {
        g_keepPlaying = false;
    }
    g_update = true;

}

// only this code remains the same as joystick.cpp
void UpdateWorld()
{
    int i;
    if (g_update) {
        g_update = false;
        system("cls");
        printf("%d", g_frame++);
        for (i = 0; i < 80; i++) {
            printf("%c", 'x');
        }
    }
}

int main(int argc, char *argv[])
{
    Init();
    g_update = true;
    UpdateWorld();
    MainMenu();
    UnInit();
}

