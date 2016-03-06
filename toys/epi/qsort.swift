
// xcrun -sdk macosx swiftc tiny.swift

func three_way_partition(inout arr:[Int], mid:Int, var n:Int)
{
    var i = 0, j = 0;
    while j <= n {
        if arr[j] < mid {
            swap(&arr[i], &arr[j]);
            i++;
            j++;
        } else if arr[j] > mid {
            swap(&arr[j], &arr[n]);
            --n;
        } else {
            ++j;
        }
    }
}

func show(var a:[Int]) 
{
    for i in 0..<a.count {
        print("\(i): \(a[i])");
    }
}

var a = [5,4,5,21,6,4,2,5,9];
var m = 5;
var len = a.count-1;
print("pre-partition");
show(a);
three_way_partition(&a, mid: m, n: len);
print("post-partition");
show(a);

