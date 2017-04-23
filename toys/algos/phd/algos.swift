#!/usr/bin/swift

print("hello")

func selection(arr:[Int]) -> Int {
    let n = arr.count;
    for var i in 0...n {
    //for i in arr.prefix(upTo:n-1) {
        //var min = i
        print("arr[i]: \(arr[i])");
        for var j in i+1...n-2 {
        //for j in arr.suffix(from: i+1) {
            print("  j: \(arr[j])");
        }
        //swap(&arr[i], &arr[min])        
        //(arr[i],arr[min]) = (arr[min],arr[i])
    }
    return n;
}


var array1 = [1,3,2,5,7,3]
var num1 = selection(arr:array1)
print("n: \(num1)");
