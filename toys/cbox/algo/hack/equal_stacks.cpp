#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

/*  input:
 *  5 3 4
 *  3 2 1 1 1
 *  4 3 2
 *  1 1 4 1
 *
 *  output:
 *  5
 */

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int max_stack(vector<int> h1, vector<int> h2, vector<int> h3)
{

    int sum_of_h1 = accumulate(h1.begin(), h1.end(), 0);
    int sum_of_h2 = accumulate(h2.begin(), h2.end(), 0);
    int sum_of_h3 = accumulate(h3.begin(), h3.end(), 0);

    int max_vector;
    if (sum_of_h1 > sum_of_h2) {
        max_vector = 1;
        if (sum_of_h3 > sum_of_h1) {
            max_vector = 3;
        }
    } else {
        max_vector = 2;
        if (sum_of_h3 > sum_of_h2) {
            max_vector = 3;
        }
    }

    return max_vector;
}

int stacks_are_equal(vector<int> h1, vector<int> h2, vector<int> h3)
{
    int equal = 0;

    int sum_of_h1 = accumulate(h1.begin(), h1.end(), 0);
    int sum_of_h2 = accumulate(h2.begin(), h2.end(), 0);
    int sum_of_h3 = accumulate(h3.begin(), h3.end(), 0);

    if (sum_of_h1 == sum_of_h2 && sum_of_h1 == sum_of_h3) {
        equal = 1;
    }

    return equal;
}

int main(){
    int n1;
    int n2;
    int n3;
    int sum;
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

    while (true) {
        if (stacks_are_equal(h1, h2, h3)) {
            //cout << "stacks are equal" << endl;
            //cout << "h1: ";
            //show(h1);
            //cout << "h2: ";
            //show(h2);
            //cout << "h3: ";
            //show(h3);
            sum = accumulate(h1.begin(), h1.end(), 0);
            break;
        }
        int max = max_stack(h1, h2, h3);
        //cout << max << endl;
        // remove top of max stack
        switch (max) {
            case 1:
                h1.erase(h1.begin());
                break;
            case 2:
                h2.erase(h2.begin());
                break;
            case 3:
                h3.erase(h3.begin());
                break;
        }

    }
    cout << sum << endl;
    return 0;
}

