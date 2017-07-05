#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


void test()
{
    string S;
    cin >> S;
    char *endptr;
    long value = std::strtol(S.c_str(), &endptr, 10);
    if (endptr == S.c_str()) {
        // Not a valid number at all
        cout << "Bad String" << endl;
    } else if (*endptr != '\0') {
        cout << "ok but..." << endl;
        // String begins with a valid number, but also contains something else after the number
    } else {
        cout << value << endl;
        // String is a number
    }
    //cout << "string: " << S << " = " << value << endl;


}

int main(){
    string S;
    cin >> S;
    int number;

    try {
        number = stoi(S);
        cout << number << endl;
    } catch(exception a) {
        cout <<"Bad String" << endl;
    }

    return 0;
}
