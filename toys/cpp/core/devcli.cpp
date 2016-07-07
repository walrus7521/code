#include "dev.h"

int main()
{
    map<string, int> menu; // = new map<string, int>();
    menu["help"] = HELP;
    menu["quit"] = QUIT;
    menu["list"] = LIST;
    create_devs();
    while (1) {
        string cmd;
        int cmdid;
        cout << "$ ";
        cin >> cmd;
        for(int i = 0; i < cmd.length(); ++i) cmd[i] = tolower(cmd[i]);
        cmdid = menu[cmd];
        switch (cmdid) {
            case HELP: 
                cout << "Helping you" << endl;
                break;
            case QUIT:
                return 0;
            case LIST:
                dm.ShowList();
                break;
            default:
                break;
        }
    }
}

