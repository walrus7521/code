#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using std::cin;     using std::cout;
using std::endl;    using std::vector;
using std::string;  using std::unordered_map;
using std::pair;    using std::copy;

// test with /usr/share/dict/words

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
    // Gets the sorted string and then insert into hash table
    unordered_map<string, vector<string>> hash;
    for (const string& s : dictionary) {
        string sorted_str(s);
        // uses sorted string as the hash code.
        sort(sorted_str.begin(), sorted_str.end());
        hash[sorted_str].emplace_back(s);
    }
    vector<vector<string>> anagrams;
   for (const pair<string, vector<string>>& p : hash) {
        // multiple strings with the same hash code => anagrams.
        if (p.second.size() >= 2) {
            anagrams.emplace_back(p.second);
        }
        
    }
    return anagrams;
}

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

int main()
{
    vector<vector<string>> anagrams;
    vector<string> dictionary;
    string line;
    int line_no = 0;

    while (getline(cin, line)) {
        ++line_no;
        vector<string> words = split(line);
        copy(words.begin(), words.end(), back_inserter(dictionary));
    }

#if 0
    for (vector<string>::const_iterator it = dictionary.begin();
            it != dictionary.end(); ++it) {
        cout << *it << endl;
    }
#endif

    anagrams = FindAnagrams(dictionary);

    for (vector<vector<string>>::const_iterator vvs = anagrams.begin();
            vvs != anagrams.end(); ++vvs) {
        for (vector<string>::const_iterator vs = vvs->begin();
                vs != vvs->end(); ++vs) {
            cout << *vs << " ";
        }
        cout << endl;
    }

    return 0;
}

