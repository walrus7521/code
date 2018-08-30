#include <string.h>
#include "StoppedState.h"
#include "StartedState.h"

static void startWatch(WatchStatePtr state)
{
    transitionToStarted(state);
}

void transitionToStopped(WatchStatePtr state)
{
    // initially with the default implementation before
    // specifying the events to be handled in the stopped
    // state
    defaultImplementation(state);
    strcpy(state->name, "Stopped\0");    
    state->start = startWatch;
}

