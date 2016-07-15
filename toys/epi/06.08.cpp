#include <iostream>
#include <vector>

using namespace std;

// A robot needs to travel along a path that includes serveral ascents
// and descents. When it goes up, it uses its battery to power the motor
// and when it descends, it recovers the energy which is stored in the
// battery. The battery recharging process is ideal: on descending, every
// Joule of gravitational potential energy converts to a Joule of electrical
// energy which is stored in the battery. The battery has a limited capacity
// and once it reaches this capacity, the energy in descending is lost.

// Design an algorithm that takes a sequence of n 3-dimensional coordinates
// to be traversed, and returns the minimum battery capacity needed to 
// complete the journey. The robot begins with the battery fully charged.

struct VECTOR3 {
    float x, y, z;
};

float CapacityNeeded(vector<VECTOR3>& journey) {
    return 0.0f;
}

void show(vector<VECTOR3> journey) {
    for (std::vector<VECTOR3>::iterator vi = journey.begin();
            vi != journey.end(); ++vi) {
        cout << "x: " << vi->x << endl;
        cout << "y: " << vi->y << endl;
        cout << "z: " << vi->z << endl;
    }
}

int main()
{
    vector<VECTOR3> journey;
    VECTOR3 v1 = {1.0, 2.0, 3.0};
    VECTOR3 v2 = {2.0, 3.0, 4.0};
    VECTOR3 v3 = {3.0, 4.0, 5.0};
    journey.push_back(v1);
    journey.push_back(v2);
    journey.push_back(v3);
    show(journey);
}
