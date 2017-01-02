#include "pch.hpp"
#include "Hash.hpp"

using namespace std;


void test_hash()
{
    Hash<string, int> hash;// = Hash_create<string, int>(13, 15);
    Hash_set(&hash, make_pair(string("bart"), 42));
    Hash_set(&hash, make_pair(string("cindy"), 36));
    Hash_show(&hash);
}

int main()
{
    test_hash();
}

