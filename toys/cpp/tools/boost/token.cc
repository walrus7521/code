#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

vector<string> labels;

class send_sparse {
public:
    send_sparse(int io, int dir, int data, int port, int slot, int ncq, int size, int immed): 
        io(io), dir(dir), data(data), port(port), slot(slot), ncq(ncq), size(size), immed(immed) {}
    void show() {
        cout << "SEND_SPARSE(" << io << ", " << dir << ", " << data << ", " << port << ", " << slot << ", " << ncq << ", " << size << ", " << immed << ")" << endl;
    }
private:
    int io, dir, data, port, slot, ncq, size, immed;
};

int do_mode(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_scenario(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_send(tokenizer<char_separator<char>> tokens) {
    string str;
    int i = 0;
    int io, dir, data, port, slot, ncq, size, immed;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        str = *it;
        stringstream tok(str);
        switch (i) {
            case  1: tok >> io; break;
            case  2: if (*it == "IN") dir = 0; else dir = 1; break;
            case  3: tok >> data; break;
            case  4: tok >> port; break;
            case  5: tok >> slot; break;
            case  6: if (*it == "NCQ") ncq = 1; else ncq = 0; break;
            case  7: tok >> size; break;
            case  8: break;
            case  9: break;
            case 10: if (*it == "N") immed = 0; else immed = 1; break;
        }
        i++;
    }
    send_sparse ss(io, dir, data, port, slot, ncq, size, immed);
    ss.show();
    return 0;
}

int do_ring(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_activate(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_associate(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_wait(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_delay(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_signal(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 1) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_end(tokenizer<char_separator<char>> tokens) {
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}

int do_if(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 2) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_command(tokenizer<char_separator<char>> tokens) {
// here's where we grab the label
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 2) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_command_completion_status(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 2) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

int do_data_block(tokenizer<char_separator<char>> tokens) {
    int i = 0;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (i == 2) cout << "(";
        cout << *it << " ";
        i++;
    }
    cout << ")" << endl;
    return 0;
}

typedef int(*p_func) (tokenizer<char_separator<char>> tokens);
map<string, p_func> my_parsers;
void setup_hash() {
    my_parsers["TRANSPORT_MODE"] = do_mode;
    my_parsers["SCENARIO"] = do_scenario;
    my_parsers["SEND_SPARSE"] = do_send;
    my_parsers["RING_SPARSE"] = do_ring;
    my_parsers["ACTIVATE"] = do_activate;
    my_parsers["ASSOCIATE"] = do_associate;
    my_parsers["WAIT_ON_SIGNAL"] = do_wait;
    my_parsers["DELAY"] = do_delay;
    my_parsers["SIGNAL"] = do_signal;
    my_parsers["END"] = do_end;
    my_parsers["IF"] = do_if;
    my_parsers["COMMAND"] = do_command;
    my_parsers["COMMAND_COMPLETION_STATUS"] = do_command_completion_status;
    my_parsers["DATA_BLOCK"] = do_data_block;
}

int parse(string text)
{
    char_separator<char> sep(", )(");
    tokenizer<char_separator<char>> tokens(text, sep);
    list<string> tokenList;
    for (tokenizer<char_separator<char>>::iterator it = tokens.begin();
        it != tokens.end();
        ++it) {
        if (my_parsers[*it]) {
            my_parsers[*it](tokens);
            return 0;
        }
        //else cout << "unknown: " << *it << "." << endl; 
    }
    return -1;
}

int main(int argc, char** argv)
{
    string line;
    setup_hash();
    while (getline(cin, line)) {
        parse(line);
    }
}

