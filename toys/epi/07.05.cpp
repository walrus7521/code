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

map<int, string> dial;

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


    dial[1] = "";
    dial[2] = "abc";
    dial[3] = "def";
    dial[4] = "ghi";
    dial[5] = "jkl";
    dial[6] = "mno";
    dial[7] = "pqrs";
    dial[8] = "tuv";
    dial[9] = "wxyz";
    dial[0] = "";
}

int spin()
{
}

void mnemonic(string num) {
    for (int i = 0; i < num.size(); ++i) {
        int v = num[i] - '0';
        printf("num[%d] = %c => %d => %s\n", i, num[i], v, dial[v].c_str());
    }
}


int main()
{
    init();
    mnemonic("4568519");
}
