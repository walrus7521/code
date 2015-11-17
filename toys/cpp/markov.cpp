#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::istream;
using std::deque;
using std::vector;
using std::string;;
using std::map;

typedef deque<string> Prefix;
map<Prefix, vector<string>> statetab;
char NONWORD[] = "\n";

#define MAXGEN 10000
#define NPREF  2

void add(Prefix& prefix, const string& s)
{
    if (prefix.size() == NPREF) {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

void build(Prefix& prefix, istream& in)
{
    string buf;
    while (in >> buf)
        add(prefix, buf);
}

void generate(int nwords) 
{
    Prefix prefix;
    int i;

    for (i = 0; i < NPREF; i++)
        add(prefix, NONWORD);

    for (i = 0; i < nwords; i++) {
        vector<string>& suf = statetab[prefix];
        const string& w = suf[rand() % suf.size()];
        if (w == NONWORD)
            break;
        cout << w << "\n";
        prefix.pop_front();
        prefix.push_back(w);
    }
}

int main(void)
{
    int nwords = MAXGEN;
    Prefix prefix;

    for (int i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    build(prefix, cin);
    add(prefix, NONWORD);
    generate(nwords);
    return 0;
}
