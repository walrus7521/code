#include <iostream>
#include <iomanip>

using namespace std;

int lookup(int a[][2], int rows, int value)
{
    int i, index;
    if (value < a[0][0]) return 0;
    
    for (i = 1; i < rows; i++) {
        if (value < a[i][0]) return i;
    }
    return rows-1;
}


int main()
{
    int arry[3][2] = {{10, 2}, // breaks and slopes
                      {20, 5}, 
                      {30, 4}};

    for (int row = 0; row < 3; row++) {
        cout << setw(3) << arry[row][0] << " : " << arry[row][1] << endl;
    }

    int rows = 3;
    int value;
    int idx;
    int slope;
    value = 1;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    cout << "lookup: " << value << " : slope: " << slope << endl;
    value = 10;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    cout << "lookup: " << value << " : slope: " << slope << endl;
    value = 15;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    cout << "lookup: " << value << " : slope: " << slope << endl;
    value = 20;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    cout << "lookup: " << value << " : slope: " << slope << endl;

    return 0;
}

