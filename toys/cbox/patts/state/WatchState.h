#ifndef WATCH_STATE_H
#define WATCH_STATE_H

typedef struct WatchState* WatchStatePtr;

// pointers ot functions
typedef void (*EventStartFunc)(WatchStatePtr);
typedef void (*EventStopFunc)(WatchStatePtr);

struct WatchState
{
    EventStartFunc start;
    EventStopFunc  stop;
    char name[16];
};

void defaultImplementation(WatchStatePtr state);

#endif // WATCH_STATE_H
