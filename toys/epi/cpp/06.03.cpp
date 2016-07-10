#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

/*
 * Multiply two big integers

 * Write a function that takes two strings representing integers, and
 * returns an integer representing their product. For example, since
 * 193707721 X -761838257287 = -147573952589676412927, if the inputs are
 * "193707721" and "-761838257287", your function should return 
 * "147573952589676412927".
 */

string multiply(string num1, string num2)
{
    bool is_positive = true;
    if (num1.front() == '-') {
        is_positive = !is_positive;
        num1 = num1.substr(1);
    }
    if (num2.front() == '-') {
        is_positive = !is_positive;
        num2 = num2.substr(1);
    }
    // reverse the digits
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    vector<int> result(num1.size() + num2.size(), 0);
    for (int i = 0; i < num1.size(); ++i) {
        for (int j = 0; j < num2.size(); ++j) {
            result[i+j] += (num1[i] - '0') * (num2[j] - '0');
            result[i+j+1] += result[i+j]/10;
            result[i+j] %= 10;
        }
    }
    // convert to string in reverse and skip leading zeros
    int i = num1.size() + num2.size() - 1;
    while (result[i] == 0 && i != 0) {
        --i;
    }
    stringstream ss;
    if (!is_positive && result[i] != 0) { // won't print -0
        ss << '-';
    }
    while (i >= 0) {
        ss << result[i--];
    }

    return ss.str();
}

string add(string a, string b)
{
    //string a = "125";
    //string b = "456";
    string c;
    int carry = 0;
    for (int i = a.length()-1; i >= 0; --i) {
        //cout << a[i] << " + " << b[i] << " = " << endl;
        int m = a[i] - '0';
        int n = b[i] - '0';
        int s = m + n + carry;
        carry = (s > 9) ? 1 : 0;
        s %= 10;
        // ok now convert back to string.
        ostringstream convert;
        convert << s;
        c += convert.str();
        //cout << m << " + " << n << " + " << carry << " = " << s << endl;
    }
    std::reverse(c.begin(), c.end());
    //cout << a << " + " << b << " = " << c << endl;
    return c;
}

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
    BigInt operator+(BigInt& m){
        BigInt p("");
        p.num += '7';
        p.num += "77";
        cout << "add: " << num << " + " << m.num << endl;
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
//    BigInt i("123");
//    BigInt j("456");
//    BigInt k = i * j;
//    BigInt m = i + j;
//    k.Show();

//    BigInt n("998");
//    n.Show();
//    ++n;
//    n.Show();

    string a = "111";
    string b = "221";
    string c;

    //c  = add(a, b);
    //cout << a << " + " << b << " = " << c << endl;

    //c  = mult(a, b);
    c  = multiply(a, b);
    string answer = "24531";
    cout << a << " * " << b << " = " << c << endl;
    cout << "answer = " << answer << endl;

    

}

