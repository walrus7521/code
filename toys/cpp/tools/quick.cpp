#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::istream;

int main()
{
    string line;
    int line_no = 0;
    vector<string> lines;

    while (getline(cin, line)) {
        ++line_no;
        lines.push_back(line);
    }

    line_no = 0;
    for (vector<string>::const_iterator it = lines.begin();
            it != lines.end(); ++it) {
        cout << "line: " << line_no++ << ": " << *it << endl;
    }

    return 0;
}

