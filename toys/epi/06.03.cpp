#include <iostream>
#include <string>

using namespace std;

/*
 * Multiply two big integers
 * 
 * Certain applications require arbitrary precision arithmetic. One way
 * to achieve this is to use strings to represent integers,e.g., with
 * one digit or negative sign per character entry, with the most significant
 * digit appearing first.

 * Write a function that takes two strings representing integers, and
 * returns an integer representing their product. For example, since
 * 193707721 X -761838257287 = -147573952589676412927, if the inputs are
 * "193707721" and "-761838257287", your function should return 
 * "147573952589676412927".
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
    BigInt* operator*(BigInt& m){
        BigInt *p = new BigInt("333");
        cout << "multiply\n";
        m.Show();
        Show();
        return p;
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
    BigInt i("111");
    BigInt j("222");
    BigInt *k;
    i.Show();
    ++i;
    i.Show();
    k = i * j;
    k->Show();
}

