#include <iostream>
#include <string>

using namespace std;

/* Widely deployed spreadsheets use an alphabetical encoding of the successive
 * columns.  Specifically, consecutive columns are identified by "A", "B", "C",
 * ... "X", "Y", "Z", "AA", "AB", ..., "ZZ", "AAA", "BBBB", ...
 * 
 * Implememnt a function that converts Excel column ids to the corresponding
 * integer, with "A" = 1.  How would you test your code?
 */

int column_id(string& id)
{
    int x = 1, n;
    for (int i = id.size()-1; i >= 0; --i) {
        n += (id[i] - 'A' + 1) * x; 
        cout << id[i] << " : " << n << endl;
        x *= 26;
    }
    cout << "id: " << id << " => " << n << endl;
    return 0;
}

int main()
{
    string s = "BA";
    int id = column_id(s);
}
