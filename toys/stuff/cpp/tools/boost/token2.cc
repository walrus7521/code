#include <iostream>
#include <string>
#include <list>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

int do_mode(list<string> tokenList, int key) {
    cout << "mode : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_scenario(list<string> tokenList, int key) {
    cout << "scenario : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_send(list<string> tokenList, int key) {
    cout << "send : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_ring(list<string> tokenList, int key) {
    cout << "ring : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_activate(list<string> tokenList, int key) {
    cout << "activate : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_wait(list<string> tokenList, int key) {
    cout << "wait : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_end(list<string> tokenList, int key) {
    cout << "end : " << endl;
    BOOST_FOREACH(string t, tokenList)
        cout << "<" << t << ">" << endl;
    return 0;
}

int do_mode2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "mode : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_scenario2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "scenario : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_send2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "send : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_ring2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "ring : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_activate2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "activate : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_wait2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "wait : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

int do_end2(tokenizer<char_separator<char>> tokens, int key) {
    cout << "end : " << endl;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << "." << endl;
    }
    return 0;
}

typedef int(*p_func2) (tokenizer<char_separator<char>> tokens, int key);
map<string, p_func2> my_parsers2;
void setup_hash2() {
    my_parsers2["TRANSPORT_MODE"] = do_mode2;
    my_parsers2["SCENARIO"] = do_scenario2;
    my_parsers2["SEND_SPARSE"] = do_send2;
    my_parsers2["RING_SPARSE"] = do_ring2;
    my_parsers2["ACTIVATE"] = do_activate2;
    my_parsers2["WAIT_ON_SIGNAL"] = do_wait2;
    my_parsers2["END"] = do_end2;
}

typedef int(*p_func) (list<string> tokenList, int key);
map<string, p_func> my_parsers;
void setup_hash() {
    my_parsers["TRANSPORT_MODE"] = do_mode;
    my_parsers["SCENARIO"] = do_scenario;
    my_parsers["SEND_SPARSE"] = do_send;
    my_parsers["RING_SPARSE"] = do_ring;
    my_parsers["ACTIVATE"] = do_activate;
    my_parsers["WAIT_ON_SIGNAL"] = do_wait;
    my_parsers["END"] = do_end;
}


void parse3(string text)
{
    list<string> tokenList;
    split(tokenList, text, is_any_of(", )("), token_compress_on);
    BOOST_FOREACH(string t, tokenList) {
        if (t[0] == '/' && t[1] == '/') {
            continue;
        }
        if (my_parsers[t]) my_parsers[t](tokenList, 7);
   }
}



int parse2(string text)
{
    char_separator<char> sep(", )(");
    tokenizer<char_separator<char>> tokens(text, sep);
    list<string> tokenList;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        //cout << *it << "." << endl;
        if (my_parsers2[*it]) my_parsers2[*it](tokens, 7);
    }
    return 0;
}


int main(int argc, char** argv)
{
    string line;
    setup_hash();
    setup_hash2();
    while (getline(cin, line)) {
        //parse3(line);
        parse2(line);
    }
}

