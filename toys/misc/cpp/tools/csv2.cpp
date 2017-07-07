#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream ip("data.csv");

    if (!ip.is_open()) cout << "error" << endl;

    string first, last, age, weight;

    while (ip.good()) {
        getline(ip, first, ',');
        getline(ip, last, ',');
        getline(ip, age, ',');
        getline(ip, weight, '\n');

        cout << "first : " << first << endl;
        cout << "last  : " << last << endl;
        cout << "age   : " << age << endl;
        cout << "weight: " << weight << endl;
        cout << endl;
    }
}
