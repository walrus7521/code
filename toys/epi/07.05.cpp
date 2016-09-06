#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<int, string> dial;

void init() {
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
