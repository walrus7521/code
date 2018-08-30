#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

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

init3()
{
    int sz = 4;
    vector<vector<int>> vvi;
    vvi.resize(sz);
    for (int i = 0; i < sz; i++) {
        vvi[i].resize(sz);
    }

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            vvi[i][j] = i+i*j;
        }
    }
    show(vvi);
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

void the_c_way()
{
    int sz = 4;
    int **c = (int **) calloc(4, sizeof(int));
    for (int i = 0; i < sz; i++) {
        c[i] = (int *) calloc(4, sizeof(int));
    }
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            c[i][j] = i+i*j;
        }
    }
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    init1();
    init2();
    init3();
    the_c_way();
    return 0;
}
