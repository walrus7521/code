#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;
using std::list;
using std::copy;

list<int> merge(list<int>& first, list<int>& second) {
    if (first.empty()) return second;
    if (second.empty()) return first;
    list<int> ret;
    list<int>::iterator first_li = first.begin();
    list<int>::iterator second_li = second.begin();
    while (first_li != first.end() && second_li != second.end()) {
        if (*first_li < *second_li) {
            ret.push_back(*first_li);
            ++first_li;
        } else
        if (*first_li == *second_li) {
            ret.push_back(*first_li);
            ret.push_back(*second_li);
            ++first_li;
            ++second_li;
        } else {
            ret.push_back(*second_li);
            ++second_li;
        }
    }
    if (first_li != first.end()) 
        copy(first_li, first.end(), back_inserter(ret));
    else
    if (second_li != second.end()) 
        copy(second_li, second.end(), back_inserter(ret));

    return ret;
}

void show(list<int> x)
{
    for (list<int>::const_iterator li = x.begin(); 
            li != x.end(); ++li) {
        cout << *li << endl;
    }
    cout << endl;
}

int main()
{
    list<int> first;
    first.push_back(1);
    first.push_back(3);
    first.push_back(5);
    first.push_back(7);
    first.push_back(9);
    show(first);

    list<int> second;
    second.push_back(0);
    second.push_back(2);
    second.push_back(4);
    second.push_back(6);
    second.push_back(8);
    show(second);

    list<int> r = merge(first, second);
    show(r);

    return 0;
}
