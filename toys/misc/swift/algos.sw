#!/usr/bin/swift

// http://jblevins.org/log/swift
// http://waynewbishop.com/swift
// https://www.weheartswift.com


func insertion(a: [Int]) -> [Int] {
    guard a.count > 1 else { return a }
    var b = a
    for i in 1..<b.count {
        var y = i
        while y > 0 && b[y] < b[y - 1] {
            swap(&b[y - 1], &b[y])
            y -= 1
        }
    }
    return b
}

func selection(a: [Int]) -> [Int] {
    guard a.count > 1 else { return a }
    var b = a
    let n = b.count
    for i in 0..<n {
        var min = i
        for j in i+1..<n {
            if b[j] < b[min] {
                min = j
            }
        }
        (b[i],b[min]) = (b[min],b[i])
    }
    return b
}

func bfs() {
}

func show_graph(g: [Int: [Int]]) {
    for (key, vertices) in g {
        for v in vertices {
            print("\(key): \(v)")
        }
    }
}

func show_array(a: [Int], name: String) {
    print(name)
    for (i) in a {
        print("\(i)")
    }
    let n = a.count
    for i in 0..<n {
        print("\(i) => \(a[i])")
    }
}

func bfs(g: [Int: [Int]], start: Int) {
//    let search_queue: Array<[Int]>?
//    search_queue.append(g[start]!)
//    searched = []
//    while search_queue:
//        item = search_queue.popleft()
//        if not item in searched:
//            if len(item):
//                print "item {}".format(item)
//                search_queue += g[item]
//                searched.append(item)
}


var a = [1,3,2,5,7,3]
//var b = insertion(a:a)
var b = selection(a:a)

print(a)
print(b)


var routes: Dictionary<Int, Array<Int>> = [
    1 : [2,4],
    2 : [3],
    3 : [7],
    4 : [5,6],
    5 : [3],
    6 : [3],
    7 : []
    ]
 
bfs(g: routes, start: 0)
show_graph(g: routes)

show_array(a:a, name: "array")

