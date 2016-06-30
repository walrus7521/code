#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
#include <cctype>

using std::string;
using std::list;
using std::find_if;
using std::isspace;
using std::cout;
using std::cin;
using std::endl;
using std::ostream_iterator;

bool space(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

template <class Out>
void split(const string& str, Out os)
{
    typedef string::const_iterator iter;

    iter i = str.begin();
    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);

        if (i != str.end())
            *os++ = string(i, j);

        i = j;
    }
}

int main()
{
    string s;
    list<string> word_list;
    while (getline(cin, s)) {
        //split(s, ostream_iterator<string>(cout, "\n"));
        split(s, back_inserter(word_list));
    }
    for (list<string>::const_iterator i = word_list.begin();
            i != word_list.end(); ++i) {
        cout << "word: " << *i << endl;
    }
    return 0;
}
