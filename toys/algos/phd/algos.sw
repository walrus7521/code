#!/usr/bin/swift

//http://waynewbishop.com/swift/traversals/

print("hello")

//func selection(arr:[Int]) -> Int {
//    let n = arr.count;
//    for var i in 0...n {
//    //for i in arr.prefix(upTo:n-1) {
//        //var min = i
//        print("arr[i]: \(arr[i])");
//        for var j in i+1...n-2 {
//        //for j in arr.suffix(from: i+1) {
//            print("  j: \(arr[j])");
//        }
//        //swap(&arr[i], &arr[min])        
//        //(arr[i],arr[min]) = (arr[min],arr[i])
//    }
//    return n;
//}

func sort(a: inout [Int]) {
       let N = a.count
       //for(var i = 0; i < N; i+=1) {
       for var i in 0...N {
         var min = i
         for var j in i+1...N {
             if(a[i] < a[j]) {
                min = j
             }
         }
         //swap(&a[i], &a[min])        
         //exch(&a, i, min) // Error: [String] not convertible to @value inout $T3
       }
}

//func exch(inout a:[String], i:Int, j:Int) {
//       let temp = a[i]
//       a[i] = a[j]
//       a[j] = temp
//}


var array1 = [1,3,2,5,7,3]
//var num1 = selection(arr:array1)
sort(a:&array1)
//print("n: \(num1)");
