#include <iostream>
#include <vector>

using namespace std;

// A robot needs to travel along a path that includes several ascents
// and descents. When it goes up, it uses its battery to power the motor
// and when it descends, it recovers the energy which is stored in the
// battery. The battery recharging process is ideal: on descending, every
// Joule of gravitational potential energy converts to a Joule of electrical
// energy which is stored in the battery. The battery has a limited capacity
// and once it reaches this capacity, the energy in descending is lost.

// Design an algorithm that takes a sequence of n 3-dimensional coordinates
// to be traversed, and returns the minimum battery capacity needed to 
// complete the journey. The robot begins with the battery fully charged.

// http://www.geeksforgeeks.org/maximum-difference-between-two-elements/
int maxDiff(vector<int> arr)
{     
    int max_diff = arr[1] - arr[0];
    int i, j;
    for(i = 0; i < arr.size(); i++) {
        for(j = i+1; j < arr.size(); j++) {        
            if(arr[j] - arr[i] > max_diff) {   
                max_diff = arr[j] - arr[i];
            }
        }    
    }          
    return max_diff;
}

int FindBatteryCapacityBook(vector<int> &h) {
    int min_height = numeric_limits<int>::max(), capacity = 0;
    for (int &height: h) {
        capacity = max(capacity, height - min_height);
        min_height = min(min_height, height);
    }
    return capacity;
}

struct VECTOR3 {
    float x, y, z;
};

int CapacityNeeded(vector<int>& journey) {
    int v = journey.front();
    int delz = 0, prez = v, maxz = 0;
    for (std::vector<int>::iterator vi = journey.begin();
            vi != journey.end(); ++vi) {
        delz += *vi - prez;
        if (delz > maxz) maxz = delz;
        prez = *vi;
        //cout << "z: " << vi->z << " prez: " << prez << " delz: " << delz << endl;
    }

    return delz;
}

void show(vector<int> journey) {
    for (std::vector<int>::iterator vi = journey.begin();
            vi != journey.end(); ++vi) {
        cout << "<" << *vi << ">" << endl;
    }
}

int main()
{

    vector<int> height;
    height.push_back(3);
    height.push_back(4);
    height.push_back(5);
    height.push_back(4);
    height.push_back(3);

    cout << "max diff: " << maxDiff2(height) << endl;

    //height.push_back(4);
    //height.push_back(5);
    int capacity = FindBatteryCapacityBook(height);
    cout << "capacity: " << capacity << endl;

    vector<int> journey;
    journey.push_back(3);
    journey.push_back(4);
    journey.push_back(5);
    journey.push_back(4);
    journey.push_back(3);
    show(journey);
    int cap = CapacityNeeded(journey);
    cout << "capacity: " << cap << endl;
}
