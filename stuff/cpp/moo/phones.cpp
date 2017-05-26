#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(string phone_nr)
{
    if (phone_nr.length() == 10) return true;
    return false;
}

string ph_format(const string& ph)
{
    string fph;
    for (int i = 0; i < 3; ++i) {
        fph += ph[i];
    }
    fph += "-";
    for (int i = 3; i < 6; ++i) {
        fph += ph[i];
    }
    fph += "-";
    for (int i = 6; i < 10; ++i) {
        fph += ph[i];
    }
    cout << "formatting: " << ph << " to: " << fph << endl;
    return fph;
}

int main()
{
    ifstream in("phonelist");
    string line, word;
    vector<PersonInfo> people;

    while (getline(in, line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    // reformat phone numbers and write to new file
    ofstream os("formatted");
    for (const auto &entry : people) {
        ostringstream formatted, badNums;
        cout << entry.name << endl;
        for (const auto &ph : entry.phones) {
            if (!valid(ph)) {
                badNums << " " << ph;
            } else {
                formatted << " " << ph_format(ph);
            }
        }
        if (badNums.str().empty()) { // no bad nums
            os << entry.name << " " << formatted.str() << endl;
        } else {
            cerr << "input error: " << entry.name 
                 << " invalid number(s) " << badNums.str() << endl;
        }
        cout << endl;
    }
}
