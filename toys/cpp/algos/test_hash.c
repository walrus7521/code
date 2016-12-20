#include <stdio.h>

#include "hash.h"

int main()
{
    hash *h = createHash(13);

    insertHash(h, "abe", 0);
    insertHash(h, "boa", 1);
    insertHash(h, "cod", 2);
    insertHash(h, "dia", 3);
    insertHash(h, "eat", 4);
    insertHash(h, "fat", 5);

    showHash(h);
#if 0

    cout << "h(7)?: " << h.lookup("goa", 7) << endl;
    cout << "h(4)?: " << h.lookup("eat", 4) << endl;

    pair<string, int> p = h.fetch("eat", 4);
    cout << "f(4): " << p.first << ": " << p.second << endl;
    pair<string, int> p2 = h.fetch("goe", 7);
    cout << "f(7): " << p2.first << ": " << p2.second << endl;
#endif

}
