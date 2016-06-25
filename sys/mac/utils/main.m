#import <objc/Object.h>

#import "helloworld.m"
int main(int argv, char* argc[])
{
    id o = [HelloWorld new];
    [o hello];

}
