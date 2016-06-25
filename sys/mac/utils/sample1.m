#import <Foundation/Foundation.h>

@interface SampleClass:NSObject
- (void)sampleWusupMethod;
- (int) max:(int) num1 secondNumber:(int) num2; 
- (NSNumber *)multiplyA:(NSNumber *)a withB:(NSNumber *)b;
@end

@implementation SampleClass
- (void)sampleWusupMethod{
   NSLog(@"Hello, World! %d\n", 42);
}
- (int) max:(int) num1 secondNumber:(int) num2 
{
   int result;
   if (num1 > num2) {
      result = num1;
   } else {
      result = num2;
   }
   return result; 
}

- (NSNumber *)multiplyA:(NSNumber *)a withB:(NSNumber *)b
{
   float number1 = [a floatValue];
   float number2 = [b floatValue];
   float product = number1 * number2;
   NSNumber *result = [NSNumber numberWithFloat:product];
   return result;
}

@end

int main()
{
    /* my first program in Objective-C */
    SampleClass *sampleClass = [[SampleClass alloc]init];
    [sampleClass sampleWusupMethod];

    int a = 100;
    int b = 200;
    int ret;
   
    ret = [sampleClass max:a secondNumber:b];
 
    NSLog(@"Max value is : %d\n", ret );

    NSNumber *x = [NSNumber numberWithFloat:10.5];
    NSNumber *y = [NSNumber numberWithFloat:10.0];   
    NSNumber *result = [sampleClass multiplyA:x withB:y];
    NSString *resultString= [result stringValue];
    NSLog(@"The product is %@",resultString);

    /* arrays */
    int n[ 10 ]; /* n is an array of 10 integers */
    int i,j;
 
    for ( i = 0; i < 10; i++ ) {
        n[ i ] = i + 100; /* set element at location i to i + 100 */
    }
    for (j = 0; j < 10; j++ ) {
        NSLog(@"Element[%d] = %d\n", j, n[j] );
    }

    return 0;
}

