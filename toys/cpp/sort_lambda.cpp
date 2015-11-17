#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <functional>

using std::cout; using std::endl; using std::cin;
using std::string; using std::vector;
using std::transform;
using std::map;

// binary predicate
bool isShorter(const string &s1, const string &s2) {
    cout << "s1: " << s1 << "= " << s1.size() << " s2: " << s2 << "= " << s2.size() << endl;
    return s1.size() < s2.size();
}

void elimDups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
 
}

string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

// lambda
void biggies(vector<string> &words,
             vector<string>::size_type sz) {
    elimDups(words);
    auto f = [](const string &a, const string &b)->bool{ return a.size() < b.size(); };
    stable_sort(words.begin(), words.end(), f);
    auto g = [sz](const string &a)->bool{ return a.size() >= sz; };
    // find_if will return an iterator to the first element at least as long as sz,
    // or a copy of words.end() is none is found.  Then we can use the iterator 
    // to see how many elements between it and words.end() exist.

    // also note, find_if takes a unary predicate, so we need to use a lambda
    // to pass in the extra parameter (sz).
    auto wc = find_if(words.begin(), words.end(), g);
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
        << " of length " << sz << " or longer" << endl;
    // now we need to print the elements in words with length sz or greater,
    // we'll use for_each, which also takes a callback.
    auto h = [](const string &s)->void{cout << s << " ";};
    for_each(wc, words.end(), h);
    cout << endl;
}

// using binding
bool check_size(const string &s, string::size_type sz) {
    return s.size() >= sz;
}

void biggies_bind(vector<string> &words,
             vector<string>::size_type sz) {
    elimDups(words);
    auto f = [](const string &a, const string &b)->bool{ return a.size() < b.size(); };
    stable_sort(words.begin(), words.end(), f);
    auto g = [sz](const string &a)->bool{ return a.size() >= sz; };
    // find_if will return an iterator to the first element at least as long as sz,
    // or a copy of words.end() is none is found.  Then we can use the iterator 
    // to see how many elements between it and words.end() exist.

    // also note, find_if takes a unary predicate, so we need to use a lambda
    // to pass in the extra parameter (sz).
    auto check_sz = bind(check_size, std::placeholders::_1, sz);
    auto wc = find_if(words.begin(), words.end(), check_sz);
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
        << " of length " << sz << " or longer" << endl;
    // now we need to print the elements in words with length sz or greater,
    // we'll use for_each, which also takes a callback.
    auto h = [](const string &s)->void{cout << s << " ";};
    for_each(wc, words.end(), h);
    cout << endl;
}



void do_bind() {
    auto check3 = bind(check_size, std::placeholders::_1, 3);
    auto check4 = bind(check_size, std::placeholders::_1, 4);
    auto check5 = bind(check_size, std::placeholders::_1, 5);
    auto check6 = bind(check_size, std::placeholders::_1, 6);
    string s = "hello";
    bool b1 = check3(s);
    if (b1) {
        cout << s << " >=  3" << endl;
    } else {
        cout << s << " <  3" << endl;
    }
}

void do_biggies() {
    vector<string> vs = {"the", "quick","red","fox","jumps","over","the","slow","red","turtle"};
    //biggies_lambda(vs, 5);
    biggies_bind(vs, 3);
}

void do_lambda() {
    auto f = []()->int{ return 42; };
    auto g = [](const string &a, const string &b)->bool{ return a.size() < b.size(); };
    auto h = [](int x, int y)->int{return x + y;};
    int z = 55;
    // captures contain a snapshot of the value, unless a reference is used.
    auto j = [&](int x)->int{return x + z;}; // using reference, z can change and I'll get the latest updated value
    auto k = [=]() mutable { return ++z; }; // mutables can change the variable
    auto m = [](int i)->int{ return i < 0 ? -i : i; }; // mutables can change the variable
    auto n = [](int i)->int{ if (i < 0) return -i; else return i; }; // mutables can change the variable
    cout << f() << endl;
    cout << h(2,3) << endl;
    z = 3;
    cout << j(7) << endl;
    cout << k() << " => z=" << z << endl;
    vector<int> vi = {2, -3, 5, -6, 1, -9};
    for (auto i : vi) cout << "i = " << i << endl;
    transform(vi.begin(), vi.end(), vi.begin(), n);
    for (auto i : vi) cout << "i = " << i << endl;
}

void do_binary_predicate() {
    vector<string> vs = {"wasup", "bartelbart", "sobriety"};
    for (auto &s : vs)
        cout << "s = " << s << endl;
    sort(vs.begin(), vs.end(), isShorter); // length sort
    //sort(vs.begin(), vs.end()); // alpha sort
    cout << endl;
    for (auto &s : vs)
        cout << "s = " << s << endl;
}

void do_unique() {
    vector<string> vs = {"bart", "bart", "cindy", "bart", "cindy"};
    for (auto &s : vs)
        cout << "s = " << s << endl;
    cout << endl;
    sort(vs.begin(), vs.end());
    for (auto &s : vs)
        cout << "s = " << s << endl;
    cout << endl;
    auto end_unique = unique(vs.begin(), vs.end());
    vs.erase(end_unique, vs.end());
    for (auto &s : vs)
        cout << "s = " << s << endl;
}

void do_map() {
    map<string, size_t> word_count;
    string word;
    while (cin >> word) {
        auto ret = word_count.insert({word, 1});
        if (!ret.second) {
            ++ret.first->second;
        }
    }
    for (auto &s : word_count) {
        cout << "word: " << s.first << " => " << s.second << endl;
    }
    cout << "done\n";
}

void do_map2() {
    map<string, size_t> word_count;
    string word;
    while (cin >> word) {
        ++word_count.insert({word, 1}).first->second;
    }
    for (auto &s : word_count) {
        cout << "word: " << s.first << " => " << s.second << endl;
    }
    cout << "done\n";
}

int main()
{
    //do_binary_predicate();
    //do_unique();
    //do_lambda();
    //do_biggies();
    //do_bind();
    do_map2();
    return 0;
}
