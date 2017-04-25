#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "watch.h"

typedef enum
{
    stopped,
    started
} State;

typedef enum
{
    stopEvent,
    startEvent
} Event;

#define NO_OF_STATES 2
#define NO_OF_EVENTS 2

static State TransitionTable[NO_OF_STATES][NO_OF_EVENTS] = 
{
    { stopped, started },
    { stopped, started }
};

struct DigitalStopWatch
{
    State state;
    // TimeSource source;
    // Display watchDisplay;
};

DigitalStopWatchPtr createWatch(void)
{
    DigitalStopWatchPtr instance = malloc(sizeof(*instance));
    if (NULL != instance) {
        // transition to stopped
    }
    return instance;
}

void destroyWatch(DigitalStopWatchPtr instance)
{
    free(instance);
}

void startWatch(DigitalStopWatchPtr instance)
{
    const State currentState = instance->state;
    instance->state = TransitionTable[currentState][startEvent];
}

void stopWatch(DigitalStopWatchPtr instance)
{
    const State currentState = instance->state;
    instance->state = TransitionTable[currentState][stopEvent];
}


