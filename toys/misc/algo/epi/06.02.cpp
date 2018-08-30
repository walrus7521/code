#include <iostream>
#include <string>

using namespace std;

/*
 * Increment a big integer
 * 
 * Write a function which takes as input an array A of digits encoding
 * a decimal number D and updates A to represent the number D + 1.  For
 * example, if A = <1,2,9> then you should update A to <1,3,0>.
 *
 * returns new string.
 */

class Puzzle {
public:
    virtual void Show() = 0;
    virtual int Process() = 0;
};

class BigInt : Puzzle {
public:
    BigInt(string s) {
        num = s; //new string(s);
    }
    void Show() {
        cout << num << endl;
    }
    BigInt& operator++(){
        int n = num.size(), i, msd = 0;
        string C;
        for (i = n-1; i >= 0; --i) {
            if (num[i] < '9') {
                num[i]++;
                break;
            }
            num[i] = '0';
            if (i == 0) msd = 1;
        }
        if (msd == 1) {
            C += '1';
        }
        for (i = 0; i < n; i++) {
            C += num[i];
        }
        num = C;
        return *this;
    }
    int Process() { return 0; }
private:
    string num;
};

int main()
{
    string num = "988";
    BigInt i(num);
    i.Show();
    ++i;
    i.Show();
}

