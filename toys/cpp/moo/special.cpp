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

void regexes()
{
    // find violations of "i before e except after c" rule
    // find the chars ei that follow a char other than c
    string pattern("[^c]ei"); // not c
    // we want the whole word in which the pattern is found
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern); // define regex that uses pattern
    smatch results; // holds matches
    string test_str = "receipt freind theif receive";
    if (regex_search(test_str, results, r)) { // stops after first find
        cout << results.str() << endl;
    }

#if FILE_SEARCH
    // look for case insensitive filename extenstions of cc, cC, Cc, CC
    // note: escaping '.' requires 2 '\\' one for c++ the other for escaping
    regex r2("[[:alpha:]]+\\.(cpp|cxx|cc)$", regex::icase);
    string filename;
    while (cin >> filename) {
        if (regex_search(filename, results, r2)) {
            cout << results.str() << endl;
        }
    }
#endif
    // regex error codes
    try {
        regex r3("[[:alpha:]+\\.(cpp|cxx|cc)$", regex::icase);
    } catch (regex_error e) {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }
}

int main()
{
    //tuples();
    //bitsets();
    regexes();
}

