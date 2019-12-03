#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <bitset>
#include <regex>
#include <random>
#include <cmath>
#include <cstdlib>

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
    string phone_pat = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
#if 0
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
#endif
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

    // regex_replace
    // reformat phone numbers to xxx.xxx.xxxx
    string fmt = "$2.$5.$7";
    regex r5(phone_pat);
    string number = "(908) 555-0132";
    cout << regex_replace(number, r5, fmt) << endl;
    string number2 = "morgan (509) 555-0132  862-555-0123" ;
    cout << regex_replace(number2, r5, fmt) << endl;

    // controlling matches and formatting
    using namespace std::regex_constants;
    // use format_no_copy to not output the unmatched parts
    string fmt2 = "$2.$5.$7 ";
    cout << regex_replace(number2, r5, fmt2, format_no_copy) << endl;
}

void random_numbers()
{
    // crazy random numbers, hard to use
    int seed = 42;
    default_random_engine e;
    e.seed(seed);
    for (size_t i = 0; i < 10; ++i) {
        cout << e() << " ";
    }
    cout << endl;

    default_random_engine e2(seed);
    uniform_int_distribution<unsigned> ui(0,9);
    // use above default_random_engine e
    for (size_t i = 0; i < 10; ++i) {
        cout << ui(e2) << " ";
    }
    cout << endl;

    // random reals
    uniform_real_distribution<double> ur(0,1);
    for (size_t i = 0; i < 10; ++i) {
        cout << ur(e) << " ";
    }
    cout << endl;

    // normal distribution
    normal_distribution<> n(4,1.5); // mean 4, stdev 1.5
    vector<unsigned> vals(9);
    for (size_t i = 0; i < 200; ++i) {
        unsigned v = lround(n(e)); // round to nearest int
        if (v < vals.size()) {
            ++vals[v];
        }
    }
    for (size_t j = 0; j < vals.size(); ++j) {
        cout << j << ": " << string(vals[j], '*') << endl;
    }

    // bernoulli distribution
    string resp;
    bernoulli_distribution b; // yields 0 or 1 with .5 probability
    do {
        bool first = b(e);
        cout << (first ? "We go first"
                       : "You get to go first") << endl;
    } while (cin >> resp && resp[0] == 'y');

    
}

void io_library()
{
    // bool formatting
    cout << "default bool values: " << true << " " << false
         << "\nalpha bool values: " << boolalpha
         << true << " " << false << endl;
    // undo bool formatting
    cout << boolalpha 
         << true << " "
         << noboolalpha
         << true << endl;

    // setting base for ints
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "octal:   " << oct << 20 << " " << 1024 << endl; 
    cout << "hex:     " << hex << 20 << " " << 1024 << endl; 
    cout << "decimal: " << dec << 20 << " " << 1024 << endl; 

    // indicating the base on the output
    cout << "showbase:" << endl;
    cout << showbase;
    cout << "octal:   " << oct << 20 << " " << 1024 << endl; 
    cout << "hex:     " << hex << 20 << " " << 1024 << endl; 
    cout << "decimal: " << dec << 20 << " " << 1024 << endl; 
    cout << noshowbase;

    // controlling case
    cout << "controlling case: " << endl;
    cout << uppercase << showbase << hex
         << "printed in hex: " << 20 << " " << 1024
         << nouppercase << noshowbase << dec << endl;

    // floats
    cout << "Precision: " << cout.precision()
         << ", Value: "   << sqrt(2.0) << endl;
    cout.precision(12);
    cout << "Precision: " << cout.precision()
         << ", Value: "   << sqrt(2.0) << endl;
    cout << setprecision(3);
    cout << "Precision: " << cout.precision()
         << ", Value: "   << sqrt(2.0) << endl;

    // float notation
    cout << "Notation:" << endl;
    cout << "default format: " << 100 * sqrt(2.0) << endl;
    cout << "scientific:     " << scientific << 100 * sqrt(2.0) << endl;
    cout << "fixed decimal:  " << fixed << 100 * sqrt(2.0) << endl;
    cout << "hexadecimal:    " << hexfloat << 100 * sqrt(2.0) << endl;
    cout << "use defaults:   " << defaultfloat << 100 * sqrt(2.0) << endl;
    // upper case float notation
    cout << "scientific UC:  " << scientific << uppercase << 100 * sqrt(2.0) << endl;
    cout << defaultfloat;
    // show decimal point
    cout << 10.0 << endl;
    cout << showpoint << 10.0 
         << noshowpoint << endl;
    // padding
    int i = -16;
    double d = 3.14159;
    // pad 1st column to use minimum 12 positions
    cout << "Padding:" << endl;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;
    // pad 1st col and left justify all cols
    cout << left;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;
    cout << right;
    // pad 1st col and right justify all cols
    cout << right;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;
    // pad 1st col, put padding internal to field
    cout << internal;
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;
    // pad 1st col, using # as pad char
    cout << setfill('#');
    cout << "i: " << setw(12) << i << "next col" << endl;
    cout << "d: " << setw(12) << d << "next col" << endl;
    cout << setfill(' ');

    // controlling input format - by default ignores whitespace
    //char ch;
    //while (cin >> ch)
    //    cout << ch;
    //cin >> noskipws;
    //while (cin >> ch)
    //    cout << ch;
    //cin >> skipws;
    // unformatted IO
    //while (cin.get(ch)) // preserves whitespace
    //    cout.put(ch);
    // put back IO to stream
    // use an int to hold return from get in order to support EOF
    //int ch2;
    //while ((ch2 = cin.get()) != EOF)
    //    cout.put(ch2);

    // multi-byte operations
    // use getline or see Table 17.20 multi-byte low level IO

    // random access to streams
    // read/write to same file, example
    fstream inOut("copyOut",
            fstream::ate | fstream::in | fstream::out); // ate mode positions at end of file
    if (!inOut) {
        cerr << "Unable to open file!" << endl;
        //goto error_out;
        //return EXIT_FAILURE; // defined in cstdlib
        return;
    }
    // inOut is opened in ate mode, so it start out position at the end
    auto end_mark = inOut.tellg(); // we need to remember the original EOF
    inOut.seekg(0, fstream::beg);
    size_t cnt = 0; // accumulator for byte count
    string line;
    while (inOut && inOut.tellg() != end_mark
                 && getline(inOut, line)) {
        cnt += line.size() + 1; // +1 accounts for newline
        auto mark = inOut.tellg(); // record current position so we can return to it at end of loop
        inOut.seekp(0, fstream::end); // set marker to end
        inOut << cnt;
        if (mark != end_mark) inOut << " "; 
        inOut.seekg(mark);
    }
    inOut.seekp(0, fstream::end); // seek to end
    inOut << "\n";  // newline at end

        
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
    //regexes();
    //except();
    //random_numbers();
    io_library();

}
