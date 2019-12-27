#include <iostream>
#include <fstream>
#include <list>
#include <string>

using std::string;
using std::cout;
using std::ifstream;
using std::endl;

void list(string dir)
{
    string s;
    ifstream in(dir);
    while (getline(in, s)) {
        string pat = "daemon";
        if (s.find(pat) != std::string::npos) {
            cout << "found: " << s << endl;
        }
    }
}



int main() 
{
    string dir = "/etc/aliases";
    list(dir);
}
