#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

vector<string> letterCombinations(string digits) {
    vector<string> lettComb;
    lettComb.push_back("");
    string dict[] = {"0", "1", "abc", "def", "ghi", 
                     "jkl", "mno", "pqrs", "tuv", 
                     "wxyz"};
    // loop over input digits
    for(int i = 0; i < digits.size(); ++i) {
        // current number of digits in lettComb
        int n = lettComb.size();
        // get letters corresponding to current digit
        string letters = dict[digits[i]-'0'];
        cout << "<" << letters << ">" << endl;
        // loop over size of lettComb
        for(int j = 0; j < n; ++j) {
            // loop over letters of digit
            for(int k = 1; k < letters.size(); ++k) {
                string comb = lettComb[j];  //clone lettComb[j]
                comb.push_back(letters[k]);
                lettComb.push_back(comb);
            }
            lettComb[j].push_back(letters[0]);
        }
    }
    return lettComb;
}

const int kNumTelDigits = 10;
const array<string, kNumTelDigits> M = {{"0", "1", "abc", 
                                         "def", "ghi",
                                         "jkl", "mno", 
                                         "pqrs", "tuv",
                                         "wxyz"}};

void PhoneMnemonicHelper(const string& phone_number, int digit,
                         string* partial_mnemonic,
                         vector<string>* mnemonics) {
    if (digit == phone_number.size()) {
        // all digits are processed so we add partial_mnemonics 
        // to mnemoics
        mnemonics->emplace_back(*partial_mnemonic);
    } else {
        // try all possible characters for this digit
        for (const char &c : M[phone_number[digit] - '0']) {
            (*partial_mnemonic)[digit] = c;
            PhoneMnemonicHelper(phone_number, digit+1, partial_mnemonic,
                    mnemonics);
        }
    }
}

vector<string> PhoneMnemonic(const string& phone_number) {
    string partial_mnemonic(phone_number.size(), 0);
    vector<string> mnemonics;
    PhoneMnemonicHelper(phone_number, 0, &partial_mnemonic, &mnemonics);
    return mnemonics;
}


vector<string> phone(string digits) {
    string dial[] = {"0", "1", "abc", "def", "ghi", 
                     "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> mnems;
    mnems.push_back(""); // prime the pump
    for(int i = 0; i < digits.size(); ++i) {
        int n = mnems.size(); // snapshot of n cuz mnems grows
        string letters = dial[digits[i]-'0']; // select dial position
        for (int j = 0; j < n; ++j) { // loop over current mnems
            for(int k = 1; k < letters.size(); ++k) {
                string comb = mnems[j];  //clone lettComb[j]
                comb.push_back(letters[k]);
                mnems.push_back(comb);
            }
            mnems[j].push_back(letters[0]);
        }
    }
    return mnems;
}

int main()
{
    //vector<string> vs = letterCombinations("2276696");
    //vector<string> vs = PhoneMnemonic("2276696");
    vector<string> vs = phone("2276696");
    for (int i = 0; i < vs.size(); ++i) {
        cout << vs[i] << endl;
    }

}

