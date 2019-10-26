// hello.cpp: Maggie Johnson
// Description: a program that prints the immortal saying "hello world"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    string s = "Hello World";
  
    //for(int t: {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
    //      std::cout << n << ' ';
    //  std::cout << '\n';
    for (int l: {0, 1, 2, 3, 4, 5}) {
        for (int t: {0, 1, 2, 3}) {
            cout << std::left << setw(17) << s;
        }
        cout << endl;
    }
   return 0;
}
