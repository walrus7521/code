#include <iostream>
#include <cmath>
#include <ctime>       /* time */


using namespace std;

#define PI 3.141
#define HI_NUM 25
#define HI_DIST 1000
#define TOLERANCE 20 // feet
int num_cannonballs = 0;
double Velocity = 200.0; // initial velocity of 200 ft/sec
double Gravity = 32.2; // gravity for distance calculation
int num_killed = 0;

void StartUp()
{
    srand (time(NULL));
    num_cannonballs = rand() % HI_NUM + 1;
    cout << "Welcome to Artillery." << endl;
    cout << "You are in the middle of a war and being charged by thousands of enemies." << endl;
    cout << "You have one cannon, which you can shoot at any angle." << endl;
    cout << "You only have " <<  num_cannonballs << " cannonballs for this target.." << endl;
    cout << "Let's begin..." << endl;
}

int Fire()
{
    double enemy_distance = rand() % HI_DIST + 1;
    double shot_distance;
    int killed = 0;
    cout << "The enemy is " << enemy_distance << " feet away!!!" << endl;
    do {
        double in_angle = 45 * 2 * PI / 360.0;
        cout << "What angle? ";
        cin >> in_angle;
        in_angle *= (PI / 360.0);
        // in_angle is the angle the player has entered, converted to radians.
        double time_in_air = (2.0 * Velocity * sin(in_angle)) / Gravity;
        double shot_distance = round((Velocity * cos(in_angle)) * time_in_air);
        cout << "shot dist " << shot_distance << endl;
        double miss = fabs(shot_distance - enemy_distance);
        if (miss < TOLERANCE) killed = 1;
        cout << "missed by " << miss << endl;
    } while (!killed);
    return killed;
}

int main()
{
    char done;
    StartUp(); // This displays the introductory script.
    int killed = 0;
    do {
        killed = Fire(); // Fire() contains the main loop of each round.
        if (killed) {
            num_killed++;
            cout << "You have killed " << num_killed << " enemy." << endl;
        }
        cout << "I see another one, care to shoot again? (Y/N) " << endl;
        cin >> done;
    } while (done != 'n');
    cout << "You killed " << killed << " of the enemy." << endl;
}
