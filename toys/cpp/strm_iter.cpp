#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using std::istream_iterator;
using std::ostream_iterator;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::accumulate;

void test1() {
    vector<int> vec;
    istream_iterator<int> in_iter(cin), eof;
    while (in_iter != eof) {
        vec.push_back(*in_iter++);
    }
    for (auto i : vec)
        cout << i << endl;
}

void test2() {
    istream_iterator<int> in_iter(cin), eof;
    vector<int> vec(in_iter, eof);
    for (auto i : vec)
        cout << i << endl;

}

void test3() {
    istream_iterator<int> in(cin), eof;
    cout << accumulate(in, eof, 0) << endl;
}

void test4() {
    vector<int> vec{1,2,3,4,5,6,7};
    ostream_iterator<int> out(cout, " ");
    for (auto e : vec)
        *out++ = e;
    cout << endl;
}

void test5() {
    vector<int> vec{1,2,3,4,5,6,7};
    ostream_iterator<int> out(cout, " ");
    copy(vec.begin(), vec.end(), out);
    cout << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    test5();
    return 0;
}
