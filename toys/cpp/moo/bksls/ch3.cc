#include <iostream>
#include <string>

using std::string; using std::cin;
using std::cout;   using std::endl;

/*
 * write code to read stdin a line at a time.
 * modify to read a  word at a time.
 */

int read_lines() {
    string line;
    while (getline(cin, line)) {
        cout << line << endl;
    }
}

/*
 * 
 */

int read_two1() {
    string s1, s2;
    cin >> s1 >> s2;
    if (s1 == s2) cout << "they are equal" << endl;
    else if (s1 < s2) cout << "s1 < s2" << endl;
    else if (s1 > s2) cout << "s1 > s2" << endl;
}

int read_two2() {
    string s1, s2;
    cin >> s1 >> s2;
    if (s1.size() == s2.size()) cout << "same length" << endl;
    else if (s1.size() < s2.size()) cout << "s1 length < s2 length" << endl;
    else if (s1.size() > s2.size()) cout << "s1 length > s2 length" << endl;
}

int cat_all() {
    string word, cat;
    while (cin >> word) {
        cat += word;
        cat += ' ';
    }
    cout << cat << endl;
}

int to_hex() {
    int n;
    const string hexdigits = "0123456789ABCDEF";
    decltype(hexdigits.size()) hex_sz = hexdigits.size();;
    //auto hex_sz = hexdigits.size();
    while (cin >> n) {
        if (n < hex_sz) {
            cout << n << " => " << hexdigits[n] << endl;
        }
    }
}

int chg_to_X(string str) {
    cout << str << endl;
    //for (auto &c : str) 
    for (char &c : str) 
        c = 'X';
    cout << str << endl;
}

int iter() {
    string s("somthing in the way..");
    for (auto it = s.begin(); it != s.end(); ++it)
        cout << *it << endl;
}

int main()
{
    //read_lines();
    //read_two1();
    //read_two2();
    //cat_all();
    //to_hex();
    //chg_to_X("bart");
    iter();
}
