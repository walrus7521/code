#include <cstdio>
#include <iostream>
#include <algorithm>

/*
 * problems: gcd, max product all but one, intervals
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

int sort_count = 0;
void SORT5(int S[])
{
    sort_count++;
    std::sort(S, S+5);
}

#define MAX(a,b) ((a) > (b) ? (a) : (b))
int MAX_of_3(int m[])
{
    return (MAX(m[0],MAX(m[1],m[2])));
}

int MAX_of_4(int m[])
{
    return (MAX(m[0],MAX(m[1],MAX(m[2],m[3]))));
}

// key: eliminate all x in S where there are at least 3 in S > x,
// only 5 integers will remain, and only one more call to SORT5
// is needed.
void largest_3_of_25(int S[], int len, int r[])
{
    int chk = 5;
    for (int i = 0; i < len; i += 5) {
        cout << "[" << i << " -> " << i+(chk-1) << "]" << endl;
        SORT5(&S[i]);
        show(&S[i], 5);
        cout << endl;
    }
    // now eliminate 1st 2 of each segment
    int B[15] = {0};
    for (int i = 0, j = 0; i < len; j+=3, i += 5) {
        B[j]   = S[i+2];
        B[j+1] = S[i+3];
        B[j+2] = S[i+4];
    }
    len -= 10;
    show(B, len);
    for (int i = 0; i < len; i += 5) {
        cout << "[" << i << " -> " << i+(chk-1) << "]" << endl;
        SORT5(&B[i]);
        show(&B[i], 5);
        cout << endl;
    }
    show(B, len);
    // now eliminate 1st 2 of each segment
    int C[10] = {0};
    for (int i = 0, j = 0; i < len; j+=3, i += 5) {
        C[j]   = B[i+2];
        C[j+1] = B[i+3];
        C[j+2] = B[i+4];
    }
    len -= 6;
    show(C, len);
    SORT5(C);
    show(C, 5);
    SORT5(C+5);
    show(C+5, 5);
    show(C, len);
    int D[6] = {0};
    for (int i = 0, j = 0; i < len; j+=3, i += 5) {
        D[j]   = C[i+2];
        D[j+1] = C[i+3];
        D[j+2] = C[i+4];
    }
    len -= 3;
    show(D, len);
    cout << "largest    : " << D[len-1] << endl;
    cout << "2nd largest: " << D[len-2] << endl;
    cout << "3rd largest: " << D[len-3] << endl;
 
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
    largest_3_of_25(S, len, b);
    cout << "num calls to SORT5: " << sort_count << endl;
    //show(S, len);
    //show(b, 3);
    int m[3] = {68, 44, 242};
    cout << "max of 3: " << MAX_of_3(m) << endl;
    int n[4] = {680, 2, 242, 1600};
    cout << "max of 4: " << MAX_of_4(n) << endl;
}
