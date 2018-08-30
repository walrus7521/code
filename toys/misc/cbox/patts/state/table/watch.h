#ifndef WATCH_H
#define WATCH_H

typedef struct DigitalStopWatch* DigitalStopWatchPtr;

void startWatch(DigitalStopWatchPtr instance);
void stopWatch(DigitalStopWatchPtr instance);
DigitalStopWatchPtr createWatch(void);
void destroyWatch(DigitalStopWatchPtr instance);

#endif // WATCH_H

