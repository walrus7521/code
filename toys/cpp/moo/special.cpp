#include <iostream>
#include <tuple>
#include <bitset>
#include <regex>

using namespace std;

#define BOOK    0
#define COUNT   1
#define PRICE   2

void tuples()
{
    auto item  = make_tuple("0-999-7345-X", 3, 20.00);
    auto book  = get<BOOK>(item);
    auto cnt   = get<COUNT>(item);
    auto price = get<PRICE>(item);

    cout << "bk: " << book << ", cnt: " << cnt << " , price: " << price << endl;

    typedef decltype(item) trans;
    //cout << "type of item: " << trans << endl;

    size_t sz = tuple_size<trans>::value;
    cout << "size of item: " << sz << endl;

    tuple_element<0, trans>::type tcnt = get<0>(item);
    cout << "type of cnt: " << tcnt << endl;
}

void bitsets()
{
    int const sz = 32;
    unsigned long long init = 0xdeadbeef;
    bitset<sz> bv(init);
    
    // strings in bitset
    // high subscript (right-most) chars correspond to the low-order bits
    string str("11110011010110100101001100101101");
    bitset<32> bvs1(str, 5, 4); // for bits, starting at str[5]
    bitset<32> bvs2(str, str.size()-4); // use last for chars
    string str2("11111111111110000000000011111111111111111111000000000001111111111111111111100000000000111111111111111111110000000000011111111111111111111000000000001111111111111111111100000000000111111111111111111110000000000011111111111111111111000000000001111111");
            
    bitset<256> bvs3(str2);
    
    // opertions on bitsets
    bool is_set = bvs1.any(); // are any one?
    cout << "is any set: " << is_set << endl;
    bool is_not_set = bvs1.none(); // are all zero?
    cout << "all zero? : " << is_not_set << endl;
    bool all_set = bvs1.all(); // are all set?
    cout << "all one?  : " << all_set << endl;
    cout << "bits      : " << bvs1 << endl;
    bvs1.flip();
    cout << "flipped   : " << bvs1 << endl;
    bvs1.reset(0);
    cout << "reset(0)  : " << bvs1 << endl;
    bvs1.set(2);
    cout << "set(2)    : " << bvs1 << endl;
    int test = bvs1.test(2);
    cout << "test(2)   : " << test << endl;
    int n_on = bvs1.count();
    cout << "n set     : " << n_on << endl;

    // large bitvec 256 bits
    cout << "256 bv    : " << bvs3 << endl;

    // io on bitset
    bitset<16> bits;
    cin >> bits;
    cout << "bits : " << bits << endl;
}

bool valid_phone(const smatch& m)
{
    // if there is an open parenthesis before the area code
    if (m[1].matched) {
        // must be followed by close parenthesis
        return m[3].matched &&
            (m[4].matched == 0 ||
             m[4].str() == " ");
    } else {
        // then there can't be a closing parenthesis
        return !m[3].matched &&
            m[4].str() == m[6].str();
    }
}

void regexes()
{
    regex integer("(\\+|-)?[[:digit:]]+");
    // find violations of "i before e except after c" rule
    // find the chars ei that follow a char other than c
    string pattern("[^c]ei"); // not c
    // we want the whole word in which the pattern is found
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern); // define regex that uses pattern
    smatch results; // holds matches
    string test_str = "dude wusup homi receipt freind yo yo homi wusup theif whooda man receive";
    string file = test_str;
    //if (regex_search(test_str, results, r)) { // stops after first find
    //    cout << results.str() << endl;
    //}
    // look for all occurences, not just the first one
    for (sregex_iterator it(file.begin(), file.end(), r), end_it;
            it != end_it; ++it) {
        // learn more about the context of the matches
        auto pos = it->prefix().length();
        pos = pos > 40 ? pos - 40 : 0;
        
        cout << it->prefix().str().substr(pos)  // last part of prefix
             << "\n\t\t>>> " << it->str() << " <<<\n" // matched word
             << it->suffix().str().substr(0, 40) // first part of suffix
             << endl;
    }

#define FILE_SEARCH 0
#if FILE_SEARCH
    // look for case insensitive filename extenstions of cc, cC, Cc, CC
    // note: escaping '.' requires 2 '\\' one for c++ the other for escaping
    regex r2("[[:alpha:]]+\\.(cpp|cxx|cc)$", regex::icase);
    // using subexpression
    regex r3("([[:alpha:]]+)\\.(cpp|cxx|cc)$", regex::icase);
    smatch results2; // holds matches
    string filename;
    while (cin >> filename) {
        //cout << "do file searchL: " << filename << endl;
        if (regex_search(filename, results2, r3)) {
            cout << results2.str(0) << endl; // entire match
            cout << results2.str(1) << endl; // 1st capture
            cout << results2.str(2) << endl; // 2nd capture
        }
    }
#endif
    // match phone numbers
    string phone_pat = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    regex r4(phone_pat);
    smatch m2;
    string s2;
    while (getline(cin, s2)) {
        cout << "phone line: " << s2 << endl;
        for (sregex_iterator it(s2.begin(), s2.end(), r4), end_it;
                it != end_it; ++it) {
            cout << "check it: " << it->str() << endl;
            if (valid_phone(*it)) {
                cout << "valid: " << it->str() << endl;
            } else {
                cout << "not valid: " << it->str() << endl;
            }
        }
    }

    // regex error codes
#if 0
    try {
        regex r3("[[:alpha:]+\\.(cpp|cxx|cc)$", regex::icase);
    } catch (regex_error e) {
        cout << e.code() << endl;
        cout << e.what() << endl;
        std::terminate();
    }
#endif
}

void myterminate () {
  std::cout << "terminate handler called\n";
  abort();  // forces abnormal termination
}

void except()
{
    std::set_terminate(myterminate);
    cout << "we are puking here...\n";
    try {
        throw 1;
    } catch (exception e) {
        cout << e.what() << endl;
    }
}

int main()
{
    //tuples();
    //bitsets();
    regexes();
    //except();


}

