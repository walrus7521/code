#include <stdio.h>
#include <stdlib.h>

typedef struct WatchState *WatchStatePtr;

typedef void (*EventStartFunc)(WatchStatePtr);
typedef void (*EventStopFunc)(WatchStatePtr);

struct WatchState
{
    EventStartFunc start;
    EventStopFunc stop;
};

static void defaultStop(WatchStatePtr state)
{
// we get here if the stop event isn't a supported concrete state
}

static void defaultStart(WatchStatePtr state)
{
// we get here if the start event isn't a supported concrete state
}

void defaultImplementation(WatchStatePtr state)
{
    state->start = defaultStart;
    state->stop = defaultStop;
}

void startWatch(WatchStatePtr state);
void stopWatch(WatchStatePtr state);

void transitionToStopped(WatchStatePtr state)
{
    defaultImplementation(state);
    state->start = startWatch;
}

void transitionToStarted(WatchStatePtr state)
{
    defaultImplementation(state);
    state->stop = stopWatch;
}

void startWatch(WatchStatePtr state)
{
    transitionToStarted(state);
}

void stopWatch(WatchStatePtr state)
{
    transitionToStopped(state);
}

// client starts here
struct DigitalStopWatch
{
    struct WatchState state;
    //TimeSource source;
    //Display watchDisplay;
};

DigitalStopWatchPtr createWatch(void)
{
}

void destroyWatch(DigitalStopWatchPtr instance)
{
}

void startWatch(DigitalStopWatchPtr instance)
{
}

void stopWatch(DigitalStopWatchPtr instance)
{
}


int main()
{
}

