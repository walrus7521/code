#import <Foundation/Foundation.h> 
#import <Cocoa/Cocoa.h>
#import <objc/Object.h>
 
@interface World:NSObject
{
}
-world;
@end
 
@implementation World
- world
{
 	NSLog(@"Hello World!");
 	return 0;
}
@end
 
int main(int argc, char *argv[])
{
 	id hello;
 
 	hello=[[World alloc] init];
 	[hello world];
 	
 	return 0;	
}
