#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int main(){
//************GIVEN***********************
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
//*****************************************
    h1.push_back(0);
    h2.push_back(0);
    h3.push_back(0);
    reverse(h1.begin(),h1.end());
    reverse(h2.begin(),h2.end());
    reverse(h3.begin(),h3.end());
    for(int i=1;i<=n1;i++){
        h1[i]+=h1[i-1];
        //cout<<h1[i]<<" ";
    }
    for(int i=1;i<=n2;i++){
        h2[i]+=h2[i-1];
        //cout<<h2[i]<<" ";
    }
    for(int i=1;i<=n3;i++){
        h3[i]+=h3[i-1];
        //cout<<h3[i]<<" ";
    }
    while(h1[n1]!=h2[n2]  ||  h1[n1]!=h3[n3]) {
        if(h1[n1] > h2[n2]) n1--;
        if(h1[n1] > h3[n3]) n1--;
        if(h2[n2] > h3[n3]) n2--;
        if(h1[n1] < h2[n2]) n2--;
        if(h1[n1] < h3[n3]) n3--;
        if(h2[n2] < h3[n3]) n3--;
    }
    cout<<h1[n1]<<"\n";
    return 0;
}

