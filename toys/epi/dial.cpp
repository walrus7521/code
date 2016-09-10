#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> letterCombinations(string digits) {
    vector<string> lettComb;
    lettComb.push_back("");
    string dict[] = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    for(int i = 0; i < digits.size(); ++i) {
        int n = lettComb.size();
        string letters = dict[digits[i]-'0'];
        cout << "<" << letters << ">" << endl;
        for(int j = 0; j < n; ++j) {
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

int main()
{
    vector<string> vs = letterCombinations("23");
    for (int i = 0; i < vs.size(); ++i) {
        cout << vs[i] << endl;
    }
}

