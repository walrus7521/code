#include <vector>
#include <iostream>

using namespace std;

/*  input:
 *  5 3 4
 *  3 2 1 1 1
 *  4 3 2
 *  1 1 4 
 *
 *  output:
 *  5
 */

int main(){
    int n1;
    int n2;
    int n3;
    cin >> n1 >> n2 >> n3;
    vector<int> h1(n1);
    for(int h1_i = 0;h1_i < n1;h1_i++){
       cin >> h1[h1_i];
    }
    vector<int> h2(n2);
    for(int h2_i = 0;h2_i < n2;h2_i++){
       cin >> h2[h2_i];
    }
    vector<int> h3(n3);
    for(int h3_i = 0;h3_i < n3;h3_i++){
       cin >> h3[h3_i];
    }
    return 0;
}

