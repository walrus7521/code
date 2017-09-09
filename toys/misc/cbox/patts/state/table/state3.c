#include <stdio.h>

typedef enum { kRedState = 0, kYellowState = 1, kGreenState = 2 } tState;
typedef enum { kRedLight, kYellowLight, kGreenLight } tLight;

struct sStateTableEntry {
    tLight light;
    tState go; //goEvent;
    tState stop; //stopEvent;
    tState timout; //timeoutEvent;
};

struct sStateTableEntry stateTable[] = {
    { kRedLight,    kGreenState,  kRedState,    kRedState}, // Red
    { kYellowLight, kYellowState, kYellowState, kRedState}, // Yellow
    { kGreenLight,  kGreenState,  kYellowState, kGreenState}, // Green
};

void LightOff(tLight light)
{
}

void LightOn(tLight light)
{
}

void StartTimer()
{
}

void HandleEventGo(struct sStateTableEntry *currentState)
{
    // turn off the light (unless we're just going to turn it back on
    if (currentState->light != currentState->go.light) {
        LightOff(currentState->light);
    }
    currentState = currentState->go;
    LightOn(currentState->light);
    StartTimer();
}

int main()
{
}
