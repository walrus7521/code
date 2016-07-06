#include <iostream>
#include <string>

using namespace std;

/*
 * Multiply two big integers

 * Write a function that takes two strings representing integers, and
 * returns an integer representing their product. For example, since
 * 193707721 X -761838257287 = -147573952589676412927, if the inputs are
 * "193707721" and "-761838257287", your function should return 
 * "147573952589676412927".
 */

class BigInt {
public:
    BigInt(string s) {
        num = s; //new string(s);
    }
    void Show() {
        cout << "num: " << num << endl;
    }
    BigInt operator*(BigInt& m){
        BigInt p("");
        p.num += '7';
        p.num += "77";
        cout << "multiply: " << num << " * " << m.num << endl;
        for (auto c : num) { // this -> right side
            cout << " : " << c << endl;
        }        
        for (auto c : m.num) { // parameter -> left side
            cout << " : " << c << endl;
        }        
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
    BigInt i("123");
    BigInt j("456");
    BigInt k = i * j;
    k.Show();
}

