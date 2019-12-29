#include <iostream>
#include <CoreFoundation/CoreFoundation.h>

void
myCallBack(CFNotificationCenterRef center,
           void *observer,
           CFStringRef name,
           const void *object,
           CFDictionaryRef userInfo) {
    std::cout << "Power Button Pressed" << std::endl;
}

int
main(int argc, const char * argv[])
{
    CFNotificationCenterRef distCenter;
    CFStringRef evtName = CFSTR("com.apple.logoutInitiated");
    distCenter = CFNotificationCenterGetDistributedCenter();
    if (NULL == distCenter)
        return 1;
    CFNotificationCenterAddObserver(distCenter, NULL, &myCallBack, evtName, NULL, CFNotificationSuspensionBehaviorDeliverImmediately);
    CFRunLoopRun();
    return 0;
}

