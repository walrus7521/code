#include <iostream>

using namespace std;

/*
 * Write code to compute the greatest common divisor of 2 integers.
 * For example, gcd(12, 18) = 6, and gcd(-4, 14) = 2.
 * Best solution is Euclidean algorithm.
 */

int gcd(int a, int b)
{
    int q, r;
    //If A = 0 then GCD(A,B)=B, since the GCD(0,B)=B, and we can stop.  
    if (a == 0) return b;
    //If B = 0 then GCD(A,B)=A, since the GCD(A,0)=A, and we can stop.  
    if (b == 0) return a;
    //Write A in quotient remainder form (A = B⋅Q + R)
    // a = b * q + r;
    if (a > b) {
        r = a % b;
        //Find GCD(B,R) using the Euclidean Algorithm since GCD(A,B) = GCD(B,R)
        return gcd(b, r);
    } else {
        r = b % a;
        //Find GCD(A,R) using the Euclidean Algorithm since GCD(A,B) = GCD(A,R)
        return gcd(a, r);
    }
    return 0;
}

int gcd_nr(int a, int b) {
  int temp;
  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return(a);
}

void get_input(int& a, int& b)
{
    cout << "Input 2 numbers to compute the GCD: ";
    do {
        if (!(cin >> a >> b)) {
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
        }
        break;
    } while (1);
 }

int main()
{
    int input1, input2, output, a, b;
    get_input(input1, input2);
    a = input1;
    b = input2;
    //if (a < 0) a *= -1;
    //if (b < 0) b *= -1;
    output = gcd_nr(a, b);
    cout << "Ok, the GCD(" << input1 << ", " << input2 << ") = " << output << endl;
}

