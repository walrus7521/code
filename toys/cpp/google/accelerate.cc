#include <iostream>

using namespace std;

void accelerate(int& speed, int amt)
{
    speed += amt;
}

int main()
{
    int speed, amt;
    speed = 60;
    amt = 5;
    accelerate(speed, amt);
    cout << "speed: " << speed << endl;
}
