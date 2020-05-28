#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <thread> 
#include <chrono> 

using namespace std;

enum STATES { GREEN, YELLOW, RED, SPOOKY };
// function table
void stop() { cout << "fake stop\n"; }
void start() { cout << "fake start\n"; }
void caution() { cout << "fake caution\n"; }
auto spooky = []() { cout << "fake spooky\n"; }; // lambda

map<int, void(*)()> states = {
    {GREEN,start},
    {YELLOW,caution},
    {RED,stop},
//    {SPOOKY,spooky},
};
int next_state(int state) {
    switch (state) {
        case GREEN:  return YELLOW;
        case YELLOW: return RED;
        case RED:    return GREEN;
    }
    return -1;
}
int state = GREEN;

int main()
{
    while (1) {
        states[state]();
        state = next_state(state);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
