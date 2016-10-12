#ifndef CUST_H
#define CUST_H

typedef struct DigitalStopWatch* DigitalStopWatchPtr;

void startWatch(DigitalStopWatchPtr instance);
void stopWatch(DigitalStopWatchPtr instance);
DigitalStopWatchPtr createWatch(void);
void destroyWatch(DigitalStopWatchPtr instance);

#endif // CUST_H

