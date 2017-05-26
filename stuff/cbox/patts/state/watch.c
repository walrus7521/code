#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "watch.h"
#include "WatchState.h"
#include "StartedState.h"
#include "StoppedState.h"

#if 0
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
#endif

struct DigitalStopWatch
{
    struct WatchState state;
    char name[16];
    // TimeSource source;
    // Display watchDisplay;
};

DigitalStopWatchPtr createWatch(void)
{
    DigitalStopWatchPtr instance = malloc(sizeof(*instance));
    if (NULL != instance) {
        // transition to stopped
        transitionToStopped(&instance->state);
    }
    return instance;
}

void destroyWatch(DigitalStopWatchPtr instance)
{
    free(instance);
}

void startWatch(DigitalStopWatchPtr instance)
{
    instance->state.start(&instance->state);
}

void stopWatch(DigitalStopWatchPtr instance)
{
    instance->state.stop(&instance->state);
}


