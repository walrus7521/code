#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream in(argv[1]);
    vector<string> vs;
    string s;
    //while (in >> s) {
    while (getline(in, s)) {
        vs.push_back(s);
    }

    // process list of input files
    for (auto p = argv+1; p != argv + argc; ++p) {
        ifstream input(*p);
        if (input) {
            while (getline(input, s)) {
                vs.push_back(s);
            }
        } else {
            cerr << "couldn't open: " << string(*p) << endl;
        }
    }

    for (auto is : vs) {
        cout << is << endl;
    }
}
