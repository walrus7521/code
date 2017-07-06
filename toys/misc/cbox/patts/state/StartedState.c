
#include <string.h>
#include "StoppedState.h"
#include "StartedState.h"

static void stopWatch(WatchStatePtr state)
{
    transitionToStopped(state);
}

void transitionToStarted(WatchStatePtr state)
{
    // initially with the default implementation before
    // specifying the events to be handled in the started
    // state
    defaultImplementation(state);
    strcpy(state->name, "Started\0");
    state->stop = stopWatch;
}

