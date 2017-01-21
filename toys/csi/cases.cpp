#include <cstdio>
#include <iostream>
#include <algorithm>

/*
 * problems: 
 *
 */

using namespace std;

void show(int a[], size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

/*
 * Given 25 integers and a CPU with SORT5 instruction, find
 * the 1st, 2nd and 3rd largest values using a minimum of calls
 * to SORT5.
 */

void SORT5(int S[])
{
    std::sort(S, S+5);
}

int MAX3(int S[])
{
    return 0;
}

// key: eliminate all x in S where there are at least 3 in S > x,
// only 5 integers will remain, and only one more call to SORT5
// is needed.
void largest_3(int S[], int len, int r[])
{
    int chk = 5;
    for (int i = 0; i < len; i += 5) {
        cout << "[" << i << " -> " << i+(chk-1) << "]" << endl;
        SORT5(&S[i]);
        show(&S[i], 5);
        cout << endl;
    }
}

void preamble()
{
    cout << endl;
    cout << "Given 25 integers and a CPU with SORT5 instruction, find" << endl;
    cout << "the 1st, 2nd and 3rd largest values using a minimum of calls" << endl;
    cout << "to SORT5." << endl << endl;

    cout << "key: eliminate all x in S where there are at least 3 in S > x," << endl;
    cout << "only 5 integers will remain, and only one more call to SORT5" << endl;
    cout << "is needed." << endl << endl;
}

int main()
{
    // find 87, 90, 98, ie the 3 largest numbers
    int S[] = {12,2,1,15,3,4,16,33,44,5,55,66,23,45,67,98,11,90,32,87,62,41,82,13,42};
    size_t len = sizeof(S) / sizeof(S[0]);
    int b[3] = {0};
    preamble();
    //std::sort(S, S+len);
    //show(S, len);
    largest_3(S, len, b);
    //show(S, len);
    //show(b, 3);
}
