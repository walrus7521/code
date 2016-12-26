#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<bool> db;
    db.push_back(true);
    db.push_back(true);
    db.push_back(false);
    db.push_back(true);

    for (int i = 0; i < db.size(); ++i) {
        cout << "b: " << db[i] << endl;
    }

}
