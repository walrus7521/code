#include <iostream>
#include <string>

using std::cin;     using std::cout; 
using std::endl;    using std::string;

int main()
{
    cout << "Please enter your first name: ";

    // read the name
    string name;
    cin >> name;

    //build the message that we intend to write
    const string greeting = "Hello, " + name + "!";
    const string border(greeting.size() + 4, '*');
    const string spaces(greeting.size() + 2, ' ');
    const int pad = 1;
    const int rows = 2 *pad + 3; // 3 => greeting + top + bottom
    const string::size_type cols = greeting.size() + 2*pad + 2;

    cout << endl;
    for (int r = 0; r != rows; ++r) {
        string::size_type c = 0;
        while (c != cols) {
            if (r == (pad + 1) && c == (pad + 1)) {
                cout << greeting;
                c += greeting.size();
            } else {
                if (r == 0 || r == (rows - 1) || c == 0 || c == (cols - 1)) {
                    //cout << border;
                    //c += border.size();
                    cout << "*";
                    ++c;
                } else {
                    cout << " ";
                    ++c;
                }
            }

        }
        cout << endl;
    }

    return 0;
}
