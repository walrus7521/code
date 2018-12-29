#include "WatchState.h"
#include <stdio.h>

static void defaultStop(WatchStatePtr state)
{
    // we'll get here if the stop event isn't
    // supported in the concrete state.
    printf("Stop event %s", state->name);
}

static void defaultStart(WatchStatePtr state)
{
    // we'll get here if the start event isn't
    // supported in the concrete state.
    printf("Start event %s", state->name);
}

void defaultShow(WatchStatePtr state)
{
    printf("showing state\n");
}

void defaultImplementation(WatchStatePtr state)
{
    state->start = defaultStart;
    state->stop  = defaultStop;
}

