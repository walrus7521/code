#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;


int main(){
    vector< vector<int> > arr(6,vector<int>(6));
    for(int arr_i = 0;arr_i < 6;arr_i++){
       for(int arr_j = 0;arr_j < 6;arr_j++){
          cin >> arr[arr_i][arr_j];
       }
    }

    int cur_sum, max_sum = INT_MIN;
    for (int r = 0; r < 6; ++r) {
        for (int c = 0; c < 6; ++c) {
            if (r < 4 && c < 4 ) {
                cur_sum = arr[r][c]   + arr[r][c+1]   + arr[r][c+2]
                                      + arr[r+1][c+1] + 
                          arr[r+2][c] + arr[r+2][c+1] + arr[r+2][c+2];

                if(cur_sum > max_sum) {
                    max_sum = cur_sum;
                }
            }
        }
    }
    cout << max_sum << endl;

    return 0;
}

