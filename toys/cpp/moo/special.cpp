#include <iostream>
#include <tuple>

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

int main()
{
    tuples();
}

