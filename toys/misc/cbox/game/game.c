#include <stdio.h>
#include <stdbool.h>

bool                 g_keepPlaying = false;
bool                 g_update = false;
int                  g_frame = 0;

// simulate joystick here
void GetInput()
{
    getchar();
    g_update = true;
}

void DisplayWorld()
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

void UpdateWorld()
{
}

void PlayGame() {
    int keepPlaying = 1;
    //while (keepPlaying) {
    while (g_keepPlaying) {
        DisplayWorld();
        GetInput();
        if (keepPlaying)
            UpdateWorld();
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
 
void Init()
{
    g_keepPlaying = true;
}

void UnInit()
{
}

int main(int argc, char *argv[]) {
    // handle command-line options
    // general setup
    Init();
    MainMenu();
    // general teardown
    UnInit();
    return 0;
}

