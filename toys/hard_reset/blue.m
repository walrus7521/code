#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <IOBluetooth/objc/IOBluetoothDeviceInquiry.h> 
#include <IOBluetoothUI/IOBluetoothUI.h>


/* https://stackoverflow.com/questions/4271014/create-a-terminal-based-bluetooth-monitor-in-xcode
 * https://github.com/Apress/os-x-ios-kernel-programming
 * https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/Bluetooth/BT_Bluetooth_On_MOSX/BT_Bluetooth_On_MOSX.html
 *
 * clang -framework Foundation -framework IOBluetooth blue.m
 *
 */

int main (int argc, const char * argv[]) { 
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init]; 
    NSLog(@"start bluetooth search"); 

    IOBluetoothDeviceInquiry *d = [[IOBluetoothDeviceInquiry new] init]; 
        [d setInquiryLength: 5]; 
        [d setUpdateNewDeviceNames: TRUE]; 
        [d start];

    [NSThread sleepUntilDate: [NSDate dateWithTimeIntervalSinceNow: 7]]; 
        [d stop]; 
        NSArray *deviceList = [d foundDevices]; 

    NSLog(@"found %d devices", [deviceList count]); 

    for(int i=0;i < [deviceList count]; i++) {

        NSScanner *theScanner = [NSScanner scannerWithString:[NSString stringWithFormat:@"%@", [deviceList objectAtIndex:i]]];


        NSString *tagDeviceName = @"mName - ";
        NSString *tagEndLine = @"\n";       

        NSString *currentDeviceName;

        // extract the mName from the current array value
        while ([theScanner isAtEnd] == NO) {
            [theScanner scanUpToString:tagDeviceName intoString:NULL];
            [theScanner scanString:tagDeviceName intoString:NULL];
            [theScanner scanUpToString:tagEndLine intoString:&currentDeviceName];           
        } // end [theScanner isAtEnd]

        NSLog(@"device name: %@", currentDeviceName);

    }


    [pool release]; 
    return 0; 
}

