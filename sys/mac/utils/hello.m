#import <objc/Object.h>

#import <stdio.h>
/** Write your Interface extending Object **/

@implementation HelloWorld:Object
-(void) hello
{
    printf("Hello World\n");
}
@end

/** Main program for the program execution entry **/
int main(int argv, char* argc[])
{

    /* Create an object */
    id o = [HelloWorld new];

    /* Pass the message 'hello' to object in the reference variable 'o' */
    [o hello];
}
