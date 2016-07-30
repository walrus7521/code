// homework from Accelerated C++

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <exception>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <cstdlib>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::istream;
using std::logic_error;
using std::domain_error;
using std::rand;
using std::srand;
using std::time;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

void dump_grammar(Grammar& g) 
{
    Grammar::const_iterator git = g.begin();
    while (git != g.end()) {
        cout << git->first << ": ";
        Rule_collection::const_iterator rcit = git->second.begin();
        while (rcit != git->second.end()) {
            Rule::const_iterator rit = rcit->begin();
            while (rit != rcit->end()) {
                cout << *rit << ", ";
                rit++;
            }
            rcit++;
        }
        cout << endl;
        git++;
    }
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

Grammar read_grammar(istream& in)
{
    Grammar ret;
    string line;

    while(getline(in, line)) {

        vector<string> entry = split(line);

        if (!entry.empty()) {
            ret[entry[0]].push_back(
                    Rule(entry.begin()+1, entry.end()));
        }
    }
    //dump_grammar(ret);
    return ret;
}

bool bracketed(const string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while (r >= n);

    //cout << "nrand(" << n << ") =  " << r << endl;
    return r;
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{
    if (!bracketed(word)) {
        ret.push_back(word);
    } else {
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
            throw logic_error("empty rule");

        const Rule_collection& c = it->second;

        const Rule& r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    }
}

vector<string> gen_sentence(const Grammar& g)
{
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}

int main()
{
    srand ( time(NULL) );

    vector<string> sentence = gen_sentence(read_grammar(cin));

    vector<string>::const_iterator it = sentence.begin();
    if (!sentence.empty()) {
        cout << *it;
        ++it;
    }

    while (it != sentence.end()) {
        cout << " " << *it;
        ++it;
    }

    cout << endl;
    return 0;

}

