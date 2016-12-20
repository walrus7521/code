#include <stdio.h>

enum {
    HAVE         = 1,
    DONT_HAVE    = 0,
    FALSE        = 0,
    TRUE         = 1,
    BEDROOM      = 1,
    HALLWAY      = 2,
    LAB          = 3,
    CONTROL_ROOM = 4
};

#define DATAFILEOUT "savegamefile.txt"
#define DATAFILEIN  "savegamefile.txt"

int uniform = DONT_HAVE;
int keyCard = DONT_HAVE;
int lighter = DONT_HAVE;
int closetKey = DONT_HAVE;
int standing = FALSE;
int light = FALSE;
int controlRoomPressureStabilization = FALSE;
int controlRoomDoorLock = TRUE;
int escapePodsLock = TRUE;
int sectorBSeal = FALSE;
int sectorCSeal = FALSE;
int doctorWillisSaved = FALSE;
int currentRoom = BEDROOM;

void initializeValues () {
    uniform = DONT_HAVE;
    keyCard = DONT_HAVE;
    lighter = DONT_HAVE;
    closetKey = DONT_HAVE;
    standing = FALSE;
    light = FALSE;
    controlRoomPressureStabilization = FALSE;
    controlRoomDoorLock = TRUE;
    escapePodsLock = TRUE;
    sectorBSeal = FALSE;
    sectorCSeal = FALSE;
    doctorWillisSaved = FALSE;
    currentRoom = BEDROOM;
}

void mainMenu {
    int NEW_GAME  = 1;
    int LOAD_GAME = 2;
    int QUIT_GAME = 3;
    
    system("cls");
    my $hereDoc = <<'END';
    ###########################################################
                         MARTIAN MYSTERY
                          VERSION 3.4.6
                      CREATOR: TYLER BURROWS
    ###########################################################
                            MAIN MENU
    1:.................................................NEW GAME
    2:................................................LOAD GAME
    3:................................................QUIT GAME
    
    ###########################################################
                    PLEASE CHOOSE FROM THE MENU
END
    print $hereDoc;
    print "\n\n>:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[a-zA-Z]/) {
        print "\n\nYou may only use numeric entries. Try again.";
        sleep 3;
        mainMenu();
    }
    elsif ($command == NEW_GAME) {
        print "Your adventure begins.\n............................";
        sleep 2;
        gameIntro();
    }
    elsif ($command == LOAD_GAME) {
        print "\n\nLoading your last game\n.........................";
        sleep 2;
        loadGame();
    }
    elsif ($command == QUIT_GAME) {
        print "\n\nQuitting Game.\n.............\nGoodbye.";
        sleep 3;
        die;
    }
    else {
        print "\n\nCommand not recognized. Choose from the menu.";
        sleep 3;
        mainMenu();
    }
}

int main()
{
    initializeValues();
    mainMenu();
}

