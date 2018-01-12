#!/usr/bin/perl

## Version: 3.15.3
## Purpose: Text based adventure game

use 5.14.1;
use warnings;

my ($command,$currentRoom,$standing,$light,$sectorBSeal,$sectorCSeal,$lighter,$controlRoomDoorLock,$doctorWillisSaved,$controlRoomPressureStabilization,$uniform,$escapePodsLock,$keyCard,$closetKey);
my (@saveArray,@loadArray);


use constant HAVE => 1;
use constant DONT_HAVE => 0;
use constant FALSE => 0;
use constant TRUE => 1;
use constant BEDROOM => 1;
use constant HALLWAY => 2;
use constant LAB => 3;
use constant CONTROL_ROOM => 4;
use constant DATAFILEOUT => './savegamefile.txt';
use constant DATAFILEIN => './savegamefile.txt';
$| = 1;
    

sub main {
    initializeValues();
    mainMenu();
    gameIntro();
    bedroomCommand();
    hallwayCommand();
    labratoryCommand();
    computerCommand();
    labNotesCommand();
    sectorACommand();
    controlRoomCommand();
    areYouSure();
    utilityRoomCommand();
    inventory();
    endingA();
    endingB();
    endingC();
    playAgain();
    saveGame();
    writeGame();
    loadGame();
    startFromLoad();
    quitMenu();
}

main();
 
sub initializeValues {
    $uniform = DONT_HAVE;
    $keyCard = DONT_HAVE;
    $lighter = DONT_HAVE;
    $closetKey = DONT_HAVE;
    $standing = FALSE;
    $light = FALSE;
    $controlRoomPressureStabilization = FALSE;
    $controlRoomDoorLock = TRUE;
    $escapePodsLock = TRUE;
    $sectorBSeal = FALSE;
    $sectorCSeal = FALSE;
    $doctorWillisSaved = FALSE;
    $currentRoom = BEDROOM;
}

sub mainMenu {
    use constant NEW_GAME => 1;
    use constant LOAD_GAME => 2;
    use constant QUIT_GAME => 3;
    
    system "cls";
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
sub gameIntro {
    system"cls";
    print "The year is 2021.";
    sleep 3;
    print "\nYou are a field scientist living in humanity's\nfirst permanent habitat on the planet mars.";
    sleep 4;
    print "\nIt is the pinnacle of technology, costing US taxpayers over\n14.7 billion dollars and taking 7 years to complete.";
    sleep 4;
    print "\nIt contains millions of dollars worth of equipment and supplies\nand houses over 350 full time residents, mainly comprised of research scientists like yourself.";
    sleep 4;
    print "\n\n\n\t\t\tWelcome to Cydonia.";
    sleep 3;
    system "cls";
    print "\n\nYou awaken with a start as you feel the entire room shake.";
    sleep 3;
    print "\n\n\t\t\tERRRN\a";
    sleep 3;
    print "\n\n\t\t\tERRRN\a";
    sleep 3;
    print "\n\n\t\t\tERRRN\a";
    sleep 3;
    print "\n\nThe habitat's alarms begin to sound,\nblaring loudly in your ear from above your bed.\nThe red light flashes bright in your face,\nburning your eyes as you open them.";
    sleep 3;
    bedroomCommand();
}

sub bedroomCommand {
    print "\n\n>:";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "inventory" or $command =~ "open inventory") {
        $currentRoom = BEDROOM;
        inventory();
    }
    elsif ($command =~ "look") {
        if ($light == FALSE) {
            print "It is very dark other than the flashing red alarm light on the ceiling.\nThere is a lamp on your nightstand.\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($light == TRUE) {
            print "The sleeping quarters are quite small.\nOnly a bed, a nightstand, a desk, a large pressure-seal door, and a dresser are in the room";
            if ($uniform == DONT_HAVE) {
                print "The chair in front of the desk has your uniform slung over it.";
                }
            if ($keyCard == DONT_HAVE) {
                print "\nYour keycard sits on the desk";
            }
            if ($lighter == DONT_HAVE) {
                print " next to an old lighter\n";
            }
            print "There are no paintings or posters on the wall, just steel painted white.\n";
            sleep 5;
        }
    }
    elsif ($command =~ "turn on" or $command =~ "turn on the lamp" or $command =~ "turn on lamp" or $command =~ "turn on the light" or $command =~ "turn on light") {
        if ($light == FALSE) {
            if ($standing == FALSE) {
                print "You reach over in bed and turn on the switch.\nThe light flickers on.\n\n";
                print "The sleeping quarters are quite small.\nOnly a bed, a nightstand, a desk, a large pressure-seal door, and a dresser are in the room";
                if ($uniform == DONT_HAVE) {
                    print " The chair in front of the desk has your uniform slung over it.";
                }
                if ($keyCard == DONT_HAVE) {
                print "\nYour keycard sits on the desk";
                }
                if ($lighter == DONT_HAVE) {
                    print " next to an old lighter\n";
                }
                print "There are no paintings or posters on the wall, just steel painted white.\n\n";
                sleep 5;
                $light = TRUE;
                bedroomCommand();
            }
        }
        elsif ($light == TRUE) {
                print "The light is already on.\n\n";
                sleep 2;
                bedroomCommand();
        }
    }
    elsif ($command =~ "nightstand" or $command =~ "night stand") {
        print "\n\nThere's nothing on here but a lamp. What a bummer.\n\n";
        sleep 2;
        bedroomCommand();
    }
    elsif ($command =~ "get out of bed" or $command =~ "stand" or $command =~ "get up") {
        if ($standing == FALSE) {
            if ($light == TRUE) {
            print "You roll out of bed and stand up facing the door.\n\n";
            sleep 2;
            $standing = TRUE;
            bedroomCommand();
            }
            elsif ($light == FALSE) {
                print "\n\nI can't really see anything.\nI should turn on the light before I get up.\n\n";
                sleep 3;
                bedroomCommand();
            }
        }
        elsif ($standing == TRUE) {
            print "You are already standing.\n\n";
            sleep 2;
            bedroomCommand();
        }
    }
    elsif ($command =~ "keycard" or $command =~ "take keycard" or $command =~ "pick up keycard" or $command =~ "grab keycard") {
        if ($light == FALSE) {
            print "\n\nWhat keycard? I can't see anything.";
            sleep 2;
            bedroomCommand();
        }
        elsif ($standing == FALSE) {
            print "You can't reach it from the bed..\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($light == TRUE) {
            if ($keyCard == HAVE) {
                print "You already have it.\n\n";
                sleep 2;
                bedroomCommand();
            }
            elsif ($keyCard == DONT_HAVE) {
                print "You pick up the keycard.\nThis will probably come in handy.\n\n";
                sleep 2;
                $keyCard = HAVE;
                bedroomCommand();
            }
        }
    }
    elsif ($command =~ "uniform" or $command =~ "put on uniform" or $command =~ "wear uniform" or $command =~ "take uniform") {
        if ($light == FALSE) {
            print "\n\nWhat uniform? I can't see anything.";
            sleep 2;
            bedroomCommand();
        }
        elsif ($standing == FALSE) {
            print "You can't reach it from the bed..\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($light == TRUE) {
            if ($uniform == HAVE) {
            print "You're already wearing your uniform.\n\n";
            sleep 2;
            bedroomCommand();
            }
            elsif ($uniform == DONT_HAVE) {
            print "You put on your uniform, a dark jumpsuit with a white lab coat.\n\n";
            sleep 2;
            $uniform = HAVE;
            bedroomCommand();
            }
        }
    }
    elsif ($command =~ "lighter" or $command =~ "pick up lighter" or $command =~ "take lighter" or $command =~ "grab lighter") {
        if ($light == FALSE) {
            print "\n\nWhat lighter? I can't see anything.\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($standing == FALSE) {
            print "You can't reach it from the bed..\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($light == TRUE) {
            if ($lighter == HAVE) {
                print "You already grabbed that.\n\n";
                sleep 3;
                bedroomCommand();
            }
            elsif ($lighter == DONT_HAVE) {
                print "You pick up the old lighter.\n\n";
                $lighter = HAVE;
                sleep 3;
                bedroomCommand();
            }
        }
    }
    elsif ($command =~ "dresser" or $command =~ "check dresser" or $command =~ "open dresser") {
        if ($light == FALSE) {
            print "\n\nWhat keycard? I can't see anything.\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($standing == FALSE) {
            print "You can't reach it from the bed..\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($light == TRUE) {
        print "There doesn't seem to be anything of use in here.\n\n";
        sleep 3;
        bedroomCommand();
        }
    }
    elsif ($command =~ "turn off the light") {
        print "\n\nI'm not afraid of the dark but I really feel like\nI should get going.\n\n";
        sleep 3;
        bedroomCommand();
    }
    elsif ($command =~ "door" or $command =~ "open door" or $command =~ "exit" or $command =~ "leave") {
        if ($standing == FALSE) {
            print "You can't reach it from the bed..\n\n";
            sleep 2;
            bedroomCommand();
        }
        elsif ($uniform == HAVE and $standing == TRUE) {
            print "You open the door and walk out into the hallway.\n\n";
            sleep 2;
            system "cls";
            $currentRoom = HALLWAY;
            hallwayCommand();
        }
        elsif ($uniform == DONT_HAVE) {
            print "You can't help but feeling you're forgetting something...\nWhatever it is, you feel naked without it....\n\n";
            sleep 2;
            bedroomCommand();
        }
    }
    elsif ($command =~ "save game" or $command =~ "save progress") {
        saveGame();
    }
    elsif ($command =~ "quit") {
       quitMenu();
    }
    else {
        print "Command not recognized. Try again.";
        sleep 2;
        bedroomCommand();
    }
}


sub hallwayCommand {
    print "\n>:";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "look") {
        print "\n\nYou are in a hallway\nThere are two doors.\nOne leading to your bedroom\nand the other leading to a utility closet.\n A sign on the wall indicates\nthe research lab is located to the right\nand the control room is located to the left.";
        sleep 4;
        hallwayCommand();
    }
    elsif ($command =~ "inventory" or $command =~ "open inventory") {
        $currentRoom = HALLWAY;
        inventory();
    }
    elsif ($command =~ "utility" or $command =~ "closet" or $command =~ "open utility closet" or $command =~ "go into utility closet") {
        if ($closetKey == DONT_HAVE) {
        print "\n\nYou try to open the utility closet door but find it to be locked.\nThe key has to be around here somewhere.\n\n";
        sleep 3;
        hallwayCommand();
        }
        else {
        print "\n\nYou use the closet key to unlock the door\nand proceed into the utility room.\n\n";
        sleep 4;
        system "cls";
        utilityRoomCommand();
        }
    }
    elsif ($command =~ "bedroom" or $command =~ "back to bedroom" or $command =~ "go in bedroom") {
        print "\n\nYou open the door to your bedroom and\nproceed back inside.";
        sleep 3;
        system "cls";
        $currentRoom = BEDROOM;
        bedroomCommand();
    }
    elsif ($command =~ "control room" or $command =~ "left" or $command =~ "go to control room" or $command =~ "go left" or $command =~ "turn left") {
        print "\n\nYou walk down the hallway to the left.\nA short distance later you see a pressure locked door\nwith a sign above it reading 'Control Room Access'\n";
        sleep 4;
        if ($controlRoomPressureStabilization == TRUE and $controlRoomDoorLock == FALSE) {
            print "\nYou twist open the pressure seal, open the door, and proceed inside.";
            sleep 4;
            system "cls";
            $currentRoom = CONTROL_ROOM;
            controlRoomCommand();
        }
        else {
            print "\nYou try to open the door, but it\nappears to be sealed.\n\n";
            sleep 4;
            hallwayCommand();
        }
        
    }
    elsif ($command =~ "go to lab" or $command =~ "go right" or $command =~ "turn right" or $command =~ "right" or $command =~ "lab") {
        print "You walk down the hallway to the right.\nYou notice quite a bit of steam coming from this direction.\nAfter turning a corner, you see the research lab.\nThe door hangs open and a steam or gas seeps out.\nYou walk in, noticing you seem to feel a little lightheaded.\n";
        sleep 8;
        system "cls";
        $currentRoom = LAB;
        labCommand();
    }
    elsif ($command =~ "save game" or $command =~ "save progress") {
        saveGame();
    }
    elsif ($command =~ "quit") {
       quitMenu();
    }
    else {
        print "\n\nCommand not recognized. Try again.\n\n";
        sleep 3;
        hallwayCommand();
    }
}

sub utilityRoomCommand {
    print "\n>:";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "look") {
        print "\n\nThe shelves and supplies have been knocked all over the room.\nHowever, you see a pair of legs sticking out from\nunder one of the shelves. It looks like Dr. Willis.\n\n";
        sleep 5;
        utilityRoomCommand();
    }
    elsif ($command =~ "dr. willis" or $command =~ "willis" or $command =~ "help" or $command =~ "legs") {
        print "\n\nYou run over to the shelves and, using all your strength, lift the\nshelf off of Dr. Willis. You pull him to the center\nof the room and assess his vital signs. His breathing\nand heart-rate are fine. He's just unconscious.\nThere's nothing I can really do now.\nI'll come back to him later.\nThere's nothing else of use in here.\nSo, I better move on for now.\nYou step back into the hallway.\n\n";
        sleep 10;
        system"cls";
        hallwayCommand();
    }
    elsif ($command =~ "leave" or $command =~ "use door" or $command =~ "hallway") {
        print "\n\nThere's something terrible happening right in front of me\nJust look! I can't leave now.\n\n";
        sleep 3;
        utilityRoomCommand();
    }
    elsif ($command =~ "save game" or $command =~ "save progress") {
        print "\n\nI can't do that here.\n\n";
        sleep 3;
        utilityRoomCommand();  
    }
    elsif ($command =~ "quit") {
       print "\n\nI can't do that here.\n\n";
       sleep 3;
       utilityRoomCommand();
    }
    else {
        print "\n\nCommand not recognized. Please try again.\n\n";
        sleep 2;
        utilityRoomCommand();
    }
}

sub labCommand {
    print ">:";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "look") {
        print "\n\nThe whole labratory is in dissaray.\nShelves are knocked over. There appears to be a liquid leaking from\none of the pipes on the wall, accompanied by a hissing noise\nand a steam-like gas rising from leak\nMost of the computer terminals in this room are\ndestroyed, but there is one that appears\nto be functioning. There is a table across\nfrom the computers with research equipment on it.\nIt is mostly beakers and test tubes.";
        print "However,\nthere is one notebook laying open";
        if ($closetKey == DONT_HAVE) {
            print " and a key on the table.\n";
        }
        sleep 5;
        labCommand();
    }
    elsif ($command =~ "inventory" or $command =~ "open inventory") {
        inventory();
    }
    elsif ($command =~ "lighter" or $command =~ "use lighter" or $command =~ "light lighter") {
       endingC();
    }
    elsif ($command =~ "computer" or $command =~ "use computer" or $command =~ "go to computer") {
        print "\n\nYou walk over to the computer terminal.\nThe computer's screensaver is active.\nThe keyboard and mouse appear to be intact.\nYou hit the space bar a few times\nand the system wakes up displaying a prompt.";
        print "\n\nPlease swipe your keycard now...";
        sleep 5;
        if ($keyCard == HAVE) {
            print "\n\nYou swipe your id card.";
            sleep 3;
            system "cls";
            computerCommand();
        }
        else {
            print "\n\nYou don't have the keycard required.\nSeems like I might have left it in my bedroom";
            sleep 3;
            labCommand();
        }
    }
    elsif ($command =~ "notebook" or $command =~ "look at notebook" or $command =~ "take notebook" or $command =~ "get notebook") {
        print "\n\nYou walk over to the table and look\nat the notebook. There are sloppily drawn\ncalculations all over the notebook.\nThey appear to be attempting to predict the trajectory\nof several objects in relation to the current\nposition of mars and the location\nof the Cydonia research station. The calculations all\npoint to an impact...\n\n";
        sleep 5;
        labCommand();
    }
    elsif ($command =~ "key" or $command =~ "pick up key" or $command =~ "take key" or $command =~ "grab key") {
        print "\n\nYou walk over to the table\nand pick up the key. The label keychain attached\nto it says 'utility closet'\n\n";
        sleep 3;
        $closetKey = HAVE;
        labCommand();
    }
    elsif ($command =~ "leave" or $command =~ "door" or $command =~ "hallway" or $command =~ "go back") {
        print "\n\nYou walk back through the door into the hallway.";
        sleep 3;
        system "cls";
        $currentRoom = HALLWAY;
        hallwayCommand();
    }
    elsif ($command =~ "save game" or $command =~ "save progress") {
        saveGame();
    }
    elsif ($command =~ "quit") {
       quitMenu();
    }
    else {
        print "\n\nCommand unrecognized. Please try again.\n\n";
        sleep 2;
        labCommand();
    }
    
}
sub computerCommand {
    system "cls";
    
    use constant LAB_NOTES => 1;
    use constant SYSTEM_STATUS => 2;
    use constant SECURITY_OPTIONS => 3;
    use constant OPEN_COMMUNICATIONS => 4;
    use constant QUIT => 5;
    
    print "\t\tCYDONIA RESEARCH CONSOLE 14.B\n\t\tPLEASE CHOOSE FROM THE FOLLOWING MENU\n
        1:..........................................VIEW LAB NOTES\n
        2:......................................VIEW SYSTEM STATUS\n
        3:........................................SECURITY OPTIONS\n
        4:.....................................OPEN COMMUNICATIONS\n
        5:....................................................QUIT\n";
    print ">:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[a-zA-Z]/) {
        print "\n\nYou may only use numeric entries. Try again.";
        sleep 3;
        computerCommand();
    }
    elsif ($command == LAB_NOTES) {
        labNotesCommand();
    }
    elsif ($command == SYSTEM_STATUS) {
        print "..............\n";
        sleep 1;
        print "....\n";
        sleep 1;
        print "Querying system status. Please wait.";
        sleep 2;
        print "\n\nOxygen converters: Stable/Running\nMain Power: partial/Sector C offline\nAuxilary Power: Offline\nCommunications: Offline\nEscape Pods: 1 and 3 active. 2, 5, and 4 offline.\n";
        sleep 6;
        computerCommand();
    }
    elsif ($command == SECURITY_OPTIONS) {
        securityOptions();
    }
    elsif ($command == OPEN_COMMUNICATIONS) {
        print "\n\nOpening communications\n..................";
        sleep 2;
        print "\nConnection established. Syncronizing Satellites.";
        sleep 1;
        print "\n..........................\n\n";
        sleep 1;
        print "Outgoing communications currently offline\ndue to solar cycle position.";
        sleep 3;
        print "Message Received from Earth communications";
        print "\n............................\n";
        sleep 3;
        print "\nMESSAGE DATE: Today\nURGENCY: 10\n
        Research Post Cydonia, our sensors indicate that\n
        there have been a series of catastrophic asteroid\n
        strikes in your sector. System sensors indicate\n
        air seal leaks in sectors B and C. In all\n
        possibility, you may all be dead. If any of you\n
        can, please respond. If communications are down\n
        immediatly proceed to escape pods for evacuation.\n
        More asteroid strikes are eminent in the next few\n
        hours. Godspeed.";
        sleep 7;
        computerCommand();
    }
    elsif ($command == QUIT) {
        print "\n\nTerminating Login\n..................\n\n";
        sleep 3;
        system "cls";
        labCommand();
    }
}

sub labNotesCommand {
    use constant APR_16 => 1;
    use constant APR_19 => 2;
    use constant MAY_1 => 3;
    use constant MAY_5 => 4;
    use constant TODAY => 5;
    use constant QUIT => 6;
    
    system "cls";
    print "\t\t CYDONIA RESEARCH LAB NOTES\n\t\tCHOOSE ENTRY TO ACCESS:\n
    1:......................................04/16/23\n
    2:......................................04/19/23\n
    3:......................................05/01/23\n
    4:......................................05/05/23\n
    5:.........................................Today\n
    6:.......................................Go Back\n";
    print ">:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[a-zA-Z]/) {
        print "\n\nYou may only use numeric entries. Try again.";
        sleep 3;
        labNotesCommand();
    }
    elsif ($command == APR_16) {
        print "\n\n\t\tEntry from 04/16/23:\nUser: Doctor Tennant\n\n
        Our first ever entry! My team and I landed earlier today at\n
        09:17 EST. My coleagues are Dr. Smith: mechanical engineer,\n
        Dr. Willis: thermodynamic engineer, Dr. Margo: doctor of\n
        astrobiology and physics, and of course myself Dr. Tennant: MD\n
        and doctor of biology. We entered the Martian atmosphere around\n
        09:00 EST. At this point, around 09:08 EST, our landing probe\n
        encountered a 5 or 6 mile high Martian dust cyclone, commonly\n
        reffered to as a Dust Devil. Luckily, we were able to release\n
        the parachute in time to avoid being pulled in and our\n
        retrorockets allowed us to redirect around the cyclone. We\n
        are currently establishing contact with the communications\n
        satellites and expect to be able to radio a full report\n
        to Earth soon.\n";
        sleep 15;
        labNotesCommand();
    }
    elsif ($command == APR_19) {
        print "\n\n\t\tEntry from 04/19/23:\nUser: Doctor Tennant\n\n
        We had a bit of a scare today. An X-5 solar flare interfered\n
        with out communications satellites, causing us to lose contact\n
        with mission support for over six hours. Our initial concern\n
        was that the satellite had been damaged and would need to be\n
        repaired somehow. However, we were able initiate a restart
        of the satellites systems using a launchable data probe.\n
        The LAKJSDKFJA;SLDL22332323XXXEWR5E2KLLL;AKLJDFKDKK\n\n
        DATA CORRUPT\nEND FILE";
        sleep 8;
        labNotesCommand();
    }
    elsif ($command == MAY_1){
        print "\n\n\t\tEntry from 05/01/23:\nUser: Doctor Tennant\n\n";
        print "We've been on Mars for almost a month now. Our initial\n
        set up and equipment tests are almost completed. Today, we\n
        launched an expedition to the 'Face of Mars' in the Cydonia
        region. A region once thought to hold proof of former life\n
        on Mars, this ancient formation strongly resembles a large face\n
        when viewed from above and at the correct angle. We took rock\n
        samples from several parts of the formation and created a 3-d\n
        mapped rendering of it, using a sonar program. We found several\n
        pockets of ice hidden several meters below the surface all around\n
        the face.\n";
        sleep 10;
        labNotesCommand();
    }
    elsif ($command == MAY_5) {
        print "\n\n\t\tEntry from 05/05/23:\nUser: Doctor Tennant\n\n";
        print "My tests have finally completed on our rock and water samples\n
        taken from the 'Face of Mars' region of Cydonia. In the rock\n
        samples we found detectable amounts the building\n
        blocks for life. However, it was the water that yielded the\n
        truly interesting results. There appears to be, and keep in\n
        mind we have not confirmed that no cross-contamination\n
        occured with the sample, some form of microbial life present\n
        in the frozen water deposits. It isn't like any organism\n
        I've ever observed before. It seems to be a sulfur based\n
        organism, that replicates incredibly quickly and is\n
        resistant to almost any poisonous compound\n";
        sleep 13;
        labNotesCommand();
    }
    elsif ($command == TODAY) {
        print "\n\n\t\tEntry from today:\nUser: Doctor Margo\n\n
        FILE NOT FOUND\nFILE MAY BE CORRUPT OR OPEN IN ANOTHER LOCATION\n
        ERROR 19456.";
        sleep 4;
        labNotesCommand();
    }
    elsif ($command == QUIT) {
        print "\n\nGoing back to menu....";
        sleep 2;
        computerCommand();
    }
    else {
        print "\n\nInvalid entry. Please choose from the menu.";
        sleep 3;
        system "cls";
        labNotesCommand();
    }
}
sub securityOptions {
    use constant CONTROL_ROOM_DOORS => 1;
    use constant ESCAPE_POD_LOCK => 2;
    use constant SECTOR_C_CONTROL => 3;
    use constant SECTOR_B_CONTROL => 4;
    use constant SECTOR_A_CONTROL => 5;
    use constant GO_BACK => 6;
    
    system "cls";
    print "\t\t CYDONIA RESEARCH SECURITY MENU\n\t\tCHOOSE ENTRY TO ACCESS:\n
    1:..............................CONTROL ROOM DOORS\n
    2:........................ESCAPE POD LOCK OVERRIDE\n
    3:................................SECTOR C CONTROL\n
    4:................................SECTOR B CONTROL\n
    5:................................SECTOR A CONTROL\n
    6:.........................................GO BACK\n";
    print ">:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[a-zA-Z]/) {
        print "\n\nYou may only use numeric entries. Try again.";
        sleep 3;
        securityOptions();
    }
    elsif ($command == CONTROL_ROOM_DOORS) {
        use constant LOCK => 1;
        use constant UNLOCK => 2;
            
        print "\n\nControl Room doors are currently: Locked\n
        Enter 1 to lock or 2 to unlock:";
        chomp ($command = <STDIN>);
        if ($command =~ /^[a-zA-Z]/) {
            print "\n\nYou may only use numeric entries. Returning to menu.";
            sleep 3;
            securityOptions();
        }
        elsif ($command == LOCK) {
            print "\n\nThe door is now locked.";
            sleep 2;
            $controlRoomDoorLock = TRUE;
            securityOptions();
        }
        elsif ($command == UNLOCK) {
            if ($controlRoomPressureStabilization == FALSE) {
                print "Cannot unlock the door at this time.\nSensors indicate a dangerous pressure leak.";
                sleep 2;
                securityOptions();
            }
            elsif ($controlRoomPressureStabilization == TRUE) {
            print "\nThe door is now unlocked.";
            sleep 2;
            $controlRoomDoorLock = FALSE;
            securityOptions();
            }
        }
        else {
            print "\n\nInvalid command. Use 1 or 2.";
            sleep 3;
            securityOptions();
        }
    }
    elsif ($command == ESCAPE_POD_LOCK) {
        use constant LOCK => 1;
        use constant UNLOCK => 2;
            
        print "\n\nEscape Pod doors are currently: Locked\n
        Enter 1 to lock or 2 to unlock:";
        chomp ($command = <STDIN>);
        if ($command =~ /^[a-zA-Z]/) {
            print "\n\nYou may only use numeric entries. Returning to menu.";
            sleep 3;
            securityOptions();
        }
        elsif ($command == LOCK) {
            print "\n\nThe door is now locked.";
            sleep 2;
            $escapePodsLock = TRUE;
            securityOptions();
        }
        elsif ($command == UNLOCK) {
            print "\nThe door is now unlocked.";
            sleep 2;
            $escapePodsLock = FALSE;
            securityOptions();
        }
    }
    elsif ($command == SECTOR_C_CONTROL) {
        print "\n\nERROR\nSector C is currently Offline. Unable to access controls.\nReturning to menu.";
        sleep 3;
        securityOptions();    
    }
    elsif ($command == SECTOR_B_CONTROL) {
        print "\n\nERROR\nSector B is currently Offline. Unable to access controls.\nReturning to menu.";
        sleep 3;
        securityOptions();
    }
    elsif ($command == SECTOR_A_CONTROL) {
        sectorACommand();
    }
    elsif ($command == GO_BACK) {
        print "\n\nGoing back to main menu....";
        sleep 3;
        system "cls";
        computerCommand();
    }    
}
sub sectorACommand {
    use constant SEAL_SECTOR_B => 1;
    use constant SEAL_SECTOR_C => 2;
    use constant PRESSURE_REPORT => 3;
    use constant GO_BACK => 4;
        
    system "cls";
    print "\t\t CYDONIA RESEARCH SECTOR A CONTROL\n\t\tCHOOSE ENTRY TO ACCESS:\n
    1:...................................SEAL SECTOR B\n
    2:...................................SEAL SECTOR C\n
    3:.................................PRESSURE REPORT\n
    4:.........................................GO BACK\n";
    print ">:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[a-zA-Z]/) {
        print "\n\nYou may only use numeric entries. Try again.";
        sleep 3;
        sectorACommand();
    }
    elsif ($command == SEAL_SECTOR_B) {
        print "\n\nSector B sealing\n.";
        sleep 1;
        print "...........";
        sleep 1;
        print "...........\n";
        sleep 1;
        print "Sector B Sealed.";
        $sectorBSeal = TRUE;
        sleep 2;
        if ($sectorCSeal == TRUE) {
            $controlRoomPressureStabilization = TRUE;
        }
        sectorACommand();
    }
    elsif ($command == SEAL_SECTOR_C) {
        print "\n\nSector C sealing\n";
        sleep 1;
        print ".........";
        sleep 1;
        print ".........\n";
        sleep 1;
        print "Sector C Sealed.";
        sleep 2;
        $sectorCSeal = TRUE;
        if ($sectorBSeal == TRUE) {
            $controlRoomPressureStabilization = TRUE;
        }
        sectorACommand();
    }
    elsif ($command == PRESSURE_REPORT) {
        if ($sectorBSeal = FALSE) {
            print "\n\nSector B: Pressure Leak. CRITICAL.";
        }
        if ($sectorCSeal = FALSE) {
            print "\n\nSector C: Pressure Leak. CRITICAL.";
        }
       if ($sectorBSeal = TRUE and $sectorCSeal = TRUE) {
            print "\n\nPressure stabilized.\nSectors B and C sealed.";
            $controlRoomPressureStabilization = TRUE;
            sleep 3;
        }
        sleep 2;
        sectorACommand();
    }
    elsif ($command == GO_BACK) {
        print "Going back to the security menu....";
        sleep 3;
        system "cls";
        securityOptions();
    }
    else {
        print "\n\nCommand not recognized. Choose from the menu.";
        sleep 3;
        sectorACommand();
    }
}
            
sub controlRoomCommand {
    print "\n>:";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "look") {
        print "\n\nThe control room consists of a central hub with\ncontrols and computers and the circular\nwalls of the room are covered in monitors\nterminals and gauges. Everything appears to be\nfunctional. There are four escape pods along the far\nwall. None of which are deployed. There is a computer terminal\nwith a visible alert message in the middle hub of the room. There is also a\ncircular window to the outside adjacent to the escape pods.";
        sleep 5;
        controlRoomCommand();
    }
    elsif ($command =~ "inventory" or $command =~ "open inventory") {
        $currentRoom = CONTROL_ROOM;
        inventory();
    }
    elsif ($command =~ "window" or $command =~ "look out window") {
        print "\n\nYou walk over to the window and peer out.\nYou weren't quite ready for what you see, however.\nYou feel your heart drop as you look through\nthe window at the charred remains of sectors B and C of the station.\nA large impact crator seems to point to some kind of large asteroid.\nYou can't imagine anyone surviving in that wreckage...";
        sleep 4;
        controlRoomCommand();
    }
    elsif ($command =~ "computer" or $command =~ "use computer" or $command =~ "go to computer") {
        print "\n\nYou walk over to the computer to get a closer\nlook at the message. It is the system monitoring\nthe vital signs of all the crew members.\nDr. Smith and Dr. Margo's vital signs are non-existent...\nHowever, mine seem fine and Dr. Willis' are weak but stable.\n";
        sleep 7;
        controlRoomCommand();
    }
    elsif ($command =~ "leave" or $command =~ "use door" or $command =~ "hallway" or $command =~ "door") {
        print "\n\nYou use the door and walk back out into the hallway.";
        $currentRoom = HALLWAY;
        sleep 3;
        hallwayCommand();
    }
    elsif ($command =~ "escape pod" or $command =~ "use escape pod" or $command =~ "escape" or $command =~ "get in escape pod") {
        if ($escapePodsLock == FALSE) {
            areYouSure();
        }
        elsif ($escapePodsLock == TRUE) {
            print "\n\nThe locks on the escape pods are currently engaged.\nIf I remember correctly, I can disable those from the labratory.";
            sleep 3;
            controlRoomCommand();
        }
    }
    elsif ($command =~ "save game" or $command =~ "save progress") {
        saveGame();
    }
    elsif ($command =~ "quit") {
       quitMenu();
    }
    else {
        print "Command not recognized. Try again.\n\n";
        sleep 3;
        controlRoomCommand();
    }
}

sub areYouSure {
    print "\n\nDo you really want to abandon the Cydonia research station\nand return to Earth? If I'm missing anything, I won't very well\nbe able to go back and get it...\n\n";
    print ">:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[1-9]/) {
        print "\n\nPlease choose yes or no.";
        sleep 2;
        areYouSure();
    }
    $command =~ tr/A-Z/a-z/;
    if ($command =~ "yes" or $command =~ "y") {
        if ($doctorWillisSaved == TRUE) {
            endingA();
        }
        else {
        endingB(); 
        }
    }
    elsif ($command =~ "no" or $command =~"n") {
        print "\n\nReturning to control room.";
        sleep 2;
        controlRoomCommand();
    }
    else {
        print "\n\nCommand not recognized. Returning to control Room.\n";
        sleep 3;
        controlRoomCommand();
    }
}

sub inventory {
    system "cls";
    print "#################################################\n";
    print "############AVAILABLE INVENTORY##################\n";
    print "#################################################";
    if ($uniform == HAVE) {
        print "\n\nOne slightly uncomfortable uniform.";
    }
    if ($keyCard == HAVE) {
        print "\n\nYour access keycard.";
    }
    if ($lighter == HAVE) {
        print "\n\nOne old lighter.";
    }
    if ($closetKey == HAVE) {
        print "\n\nThe key to the utility closet.";
    }
    sleep 5;
    if ($currentRoom == BEDROOM) {
        bedroomCommand();
    }
    elsif ($currentRoom == HALLWAY) {
        hallwayCommand();
    }
    elsif ($currentRoom == LAB) {
        labCommand();
    }
    elsif ($currentRoom == CONTROL_ROOM) {
        controlRoomCommand();
    }
    
}

sub endingA {
    print "\n\nYou prepare the escape pods for launch. One for yourself\n and one for Doctor Willis. You quickly run back to the utility room\nand carry him into the command room. You lay him down\nin one of the escape pods, activate its distress beacon, set its coordinates\nfor Earth, close the doors, and send him home. You then prepare your own pod as you watch\nDoctor Willis' pod shoot into the air out the observation window.\nYou secure the door, lock in your coordinates, and initiate the launch protocol.\nYou feel yourself pulled down hard as the escape pod's thrusters\nshoot you into the Martian atmosphere. As you depart,\nyou look back, seeing the wreckage of B and C sections scattered across the landscape.\nThe grief of the loss of your other team mates grips the pit\nof your stomach tightly. You watch a 'Dust Devil' swings past the pod,\nwhirling dust around the windows as Cydonia wane in the distance.\nYou say a silent goodbye to your fallen comrads, taking comfort\nin the fact you were at least able to save someone.\nYou close your eyes and lean your head back. 'What a trip' You think to yourself.";
    sleep 18;
    print "\n\nMission Successful.";
    sleep 3;
    playAgain();
}

sub endingB {
    print "\n\nYou prepare your escape pod for launch. You get inside, secure the doors, set your\ncoordinates for Earth, and intiate the launch protocol. You feel the thrusters kick in as you are pulled back into your seat in the pod.\nYou are lifted high into the Martian atmosphere. As you ascend, you\nlook back at the shattered remains of sectors B and C of the research station.\nYou feel a sickening sadness as the deaths of your comrads sinks in.\n'If only there was something I could have done. If I could have just saved one of them...'\nYou sigh and lean back into your seat, closing your eyes. 'It's going to be a long ride home' you think to yourself.";
    sleep 18;
    print "\n\nMission Successful...Sort of...You might have missed something...hint hint.";
    sleep 3;
    playAgain();
}

sub endingC {
    print "\n\nYou flick open the lighter and, after a few failed tries,\nit lights. However, since the labratory is currently\nleaking liquid oxygen and massive amounts of it are\nbeing converted to gas from the heat of the room.\nThe flame causes a massive explosion. Time seems to slow down\nas you see the flame grow and you feel consumed with heat.\nYour body is torn asunder into millions of little pieces\nas the explosive force ruptures the entire habitat.\nThis causes a pressure leak resulting in every little piece of you\n,along with all the lab equipment,being blown\ninto space. The report of the habitat's destruction\nand all its crew members' deaths won't even reach Earth\nfor another 14 minutes. Only one thought passes through your mind\nin your final seconds. 'Why the hell\nwould anyone bring a lighter to a pressurized oxygen habitat?";
    print "\n\n\t\t\tGAME OVER";
    sleep 18;
    playAgain();
}

sub playAgain {
    use constant YES => 'y';
    use constant NO => 'n';
    
    system "cls";
    print "\n\nWould you like to play again? Y or N?";
    print "\n>:";
    chomp ($command = <STDIN>);
    if ($command =~ /^[1-9]/) {
        print "\n\nNumerical entries not allowed. Use Y or N.";
        sleep 3;
        playAgain();
    }
    $command =~ tr/A-Z/a-z/;
    if ($command == YES) {
        main();
    }
    elsif ($command == NO) {
        print "\n\nThank you for playing!\nGoodbye!";
        sleep 2;
        die;
    }
    else {
        print "\n\nCommand not recognized. Use Y or N.";
        sleep 3;
        playAgain();
    }
    
}

sub saveGame {
    @saveArray = ();
    $saveArray[0] = $uniform;
    $saveArray[1] = $keyCard;
    $saveArray[2] = $lighter;
    $saveArray[3] = $closetKey;
    $saveArray[4] = $standing;
    $saveArray[5] = $light;
    $saveArray[6] = $controlRoomDoorLock;
    $saveArray[7] = $controlRoomPressureStabilization;
    $saveArray[8] = $sectorBSeal;
    $saveArray[9] = $sectorCSeal;
    $saveArray[10] = $doctorWillisSaved;
    $saveArray[11] = $currentRoom;
    writeGame();
}

sub writeGame {
    my $OUT;
    my $size = @saveArray;
    open ($OUT, '+>', DATAFILEOUT);
    for (my $i = 0; $i < $size; $i++) {
	print ($OUT "$saveArray[$i]");
        print ($OUT "\n");
    }
    close $OUT;
    print "\n\n\t\tGame successfully saved. Goodbye";
    sleep 3;
    mainMenu();
}

sub loadGame {
    use constant MAX_INVENTORY => 12;
    my $IN;
    my $counter = 0;
    @loadArray = ();
    open ($IN, '<', DATAFILEIN);
    while (<$IN>) {
	chomp ($loadArray[$counter] = $_);
        $counter++;
    }
    close $IN;
    startFromLoad();
}

sub startFromLoad {
    $uniform = $loadArray[0];
    $keyCard = $loadArray[1];
    $lighter = $loadArray[2];
    $closetKey = $loadArray[3];
    $standing = $loadArray[4];
    $light = $loadArray[5];
    $controlRoomDoorLock = $loadArray[6];
    $controlRoomPressureStabilization = $loadArray[7];
    $sectorBSeal = $loadArray[8];
    $sectorCSeal = $loadArray[9];
    $doctorWillisSaved = $loadArray[10];
    $currentRoom = $loadArray[11];
    system "cls";
    if ($currentRoom == BEDROOM) {
        print "\n\nLoad Successful\nCurrent Room: Bedroom\n";
        sleep 3;
        bedroomCommand();
    }
    elsif ($currentRoom == HALLWAY){
        print "\n\nLoad Successful\nCurrent Room: Hallway\n";
        sleep 3;
        hallwayCommand();
    }
    elsif ($currentRoom == LAB) {
        print "\n\nLoad Successful\nCurrent Room: Labratory\n";
        sleep 3;
        labCommand();
    }
    elsif ($currentRoom == CONTROL_ROOM) {
        print "\n\nLoad Successful\nCurrent Room: Control Room\n";
        sleep 3;
        controlRoomCommand();
    } 
}

sub quitMenu {
    use constant YES => 'y';
    use constant NO => 'n';
    
    print "\n\nDo you wish to quit without saving? y or n?\n";
    chomp ($command = <STDIN>);
    $command =~ tr/A-Z/a-z/;
    if ($command =~ /^[1-9]/) {
        print "\n\nYou may only enter letters in this field. Y for yes or N for no.";
        sleep 3;
        quitMenu();
    }
    elsif ($command == YES) {
        print "\n\nQuitting Game.\n....................";
        sleep 3;
        die;
    }
    elsif ($command == NO) {
        print "\n\nReturning to game. Type 'save game' to save your progress.";
        sleep 3;    
        if ($currentRoom == BEDROOM) {
            print "\n\nReturn Successful\nCurrent Room: Bedroom\n";
            sleep 3;
            bedroomCommand();
        }
        elsif ($currentRoom == HALLWAY){
        print "\n\nReturn Successful\nCurrent Room: Hallway\n";
        sleep 3;
        hallwayCommand();
        }
        elsif ($currentRoom == LAB) {
        print "\n\nReturn Successful\nCurrent Room: Labratory\n";
        sleep 3;
        labCommand();
        }
        elsif ($currentRoom == CONTROL_ROOM) {
        print "\n\nReturn Successful\nCurrent Room: Control Room\n";
        sleep 3;
        controlRoomCommand();
        }   
    }
    else {
        print "\n\nCommand not recognized. Use Y for yes and N for no.";
        sleep 3;
        quitMenu();
    }
}


