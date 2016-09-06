#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct _dial {
    int size;
    string letters;
    int setting;
};

struct _dial dials[10];
int current_dial = 0;

void init() {

    dials[0].size = 0;
    dials[1].size = 0;

    dials[2].size    = 3;
    dials[2].letters = "abc";
    dials[2].setting = 0;

    dials[3].size    = 3;
    dials[3].letters = "def";
    dials[3].setting = 0;

    dials[4].size    = 3;
    dials[4].letters = "ghi";
    dials[4].setting = 0;

    dials[5].size    = 3;
    dials[5].letters = "jkl";
    dials[5].setting = 0;

    dials[6].size    = 3;
    dials[6].letters = "mno";
    dials[6].setting = 0;

    dials[7].size    = 4;
    dials[7].letters = "pqrs";
    dials[7].setting = 0;

    dials[8].size    = 3;
    dials[8].letters = "tuv";
    dials[8].setting = 0;

    dials[9].size    = 4;
    dials[9].letters = "wxyz";
    dials[9].setting = 0;

    current_dial = 0;

}

int step()
{
    if (dials[9].setting == dials[9].size) {
        return 0; // we're done
    }    
    printf("step: %c\n", dials[current_dial].letters[dials[current_dial].setting]);
    if (dials[current_dial].setting == dials[current_dial].size) {
        dials[current_dial].setting = 0;
    } else {
        dials[current_dial].setting++;
    }
#if 0
    switch (current_dial) {
        case 0: 
        case 1:
            current_dial++;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            current_dial++;
            break;
        case 9:
            current_dial = 0;
            break;
        default: break;
    }
#endif
    return 1;
}

void display()
{
    //printf("display...\n");
}

void mnemonic(string num) {
    for (int i = 0; i < num.size(); ++i) {
        int v = num[i] - '0';
        printf("num[%d] = %c => %d => %s\n", i, num[i], v, dials[v].letters.c_str());
        current_dial = v;
        while (step()) {
            display();
        }
    }
}


int main()
{
    init();
    mnemonic("4568519");
}
