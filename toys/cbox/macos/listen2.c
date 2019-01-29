#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>

void notificationCallback (CFNotificationCenterRef center,
                           void * observer,
                           CFStringRef name,
                           const void * object,
                           CFDictionaryRef userInfo) {
    CFShow(CFSTR("Received notification (dictionary):"));
    // print out user info
    const void * keys;
    const void * values;
    CFDictionaryGetKeysAndValues(userInfo, &keys, &values);
    for (int i = 0; i < CFDictionaryGetCount(userInfo); i++) {
        const char * keyStr = CFStringGetCStringPtr((CFStringRef)&keys[i], CFStringGetSystemEncoding());
        const char * valStr = CFStringGetCStringPtr((CFStringRef)&values[i], CFStringGetSystemEncoding());
        printf("\t\t \"%s\" = \"%s\"\n", keyStr, valStr);
    }
}

int main (int argc, const char * argv[]) {
    CFNotificationCenterRef center = CFNotificationCenterGetLocalCenter();
    // add an observer
    CFNotificationCenterAddObserver(center, NULL, notificationCallback, 
                                    CFSTR("MyNotification"), NULL, 
                                    CFNotificationSuspensionBehaviorDeliverImmediately);
    // post a notification
    CFDictionaryKeyCallBacks keyCallbacks = {0, NULL, NULL, CFCopyDescription, CFEqual, NULL}; 
    CFDictionaryValueCallBacks valueCallbacks  = {0, NULL, NULL, CFCopyDescription, CFEqual};
    CFMutableDictionaryRef dictionary = CFDictionaryCreateMutable(kCFAllocatorDefault, 1, 
                                                                  &keyCallbacks, &valueCallbacks);
    CFDictionaryAddValue(dictionary, CFSTR("TestKey"), CFSTR("TestValue"));
    CFNotificationCenterPostNotification(center, CFSTR("MyNotification"), NULL, dictionary, TRUE);
    CFRelease(dictionary);
    // remove oberver
    CFNotificationCenterRemoveObserver(center, NULL, CFSTR("TestValue"), NULL);
    return 0;
}


