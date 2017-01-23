#include "pch.hpp"
#include "Hash.hpp"

using namespace std;

int ascii[256] = {0};

void show_ascii()
{
    for (std::uint8_t i = 0; i < 255; ++i)
        if (ascii[i] != 0) cout 
            << "ascii[" << i << "]: " 
            << ascii[i] << endl;
}

bool test_palindrome(string s)
{
    bool once = false;
    for (int i = 0; i < s.length(); ++i) ascii[s[i]]++;
    for (int i = 0; i < s.length(); ++i) {
        if (ascii[s[i]] == 1 && once == false) once = true;
        else if (ascii[s[i]] % 2 != 0) return false;
    }
    show_ascii();
    return true;
}

void test_hash()
{
    Hash<string, int> hash;// = Hash_create<string, int>(13, 15);
    Hash_set(&hash, make_pair(string("bart"), 42));
    Hash_set(&hash, make_pair(string("cindy"), 36));
    Hash_show(&hash);

    Hash<int, string> hash2;
    Hash_set(&hash2, make_pair(44, string("bart")));
    Hash_set(&hash2, make_pair(37, string("cindy")));
    Hash_show(&hash2);


}

int main()
{
    //test_hash();
    if (test_palindrome(string{"gattaacag"})) 
        cout << "is pal" << endl;
    else
        cout << "not pal" << endl;

}

