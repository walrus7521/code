#include <iostream>
#include <vector>

using namespace std;

void show(vector<vector<int>>& vvi)
{
    int cols = vvi.size();
    for (int i = 0; i < vvi.size(); ++i) {
        for (int j = 0; j < vvi[i].size(); ++j) {
            cout << vvi[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init1()
{
    vector<vector<int>> vvi;
    int rows = 2, cols = 3;
    vvi.resize( rows , vector<int>( cols ) );
    int counter = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            vvi[i][j] = counter++;
            cout << vvi[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    show(vvi);
}

void init2()
{
    std::vector<std::vector<int>> vvi { { 7, 8, 9 },
                                        { 3, 1, 2 } };
    show(vvi);
}


int main()
{
    init1();
    init2();
    return 0;
}
