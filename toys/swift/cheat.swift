#!/usr/bin/swift
import Foundation
import Cocoa


// Types
// Int, Int32, Int64, UInt, Double, Float, String
// Ints: Decimal: , Binary: 0b, Octal: 0o, Hex: 0x 

// defining/declaring variables and constants
let x = 7; // immutable
var y = 42; // mutable

// Optionals
// =========
var someString:String? = "hey there";
var someString2:String = "ho there";
println("yo \(someString)");
println("yo \(someString2)");

// optionals must be unwrapped
// test existence of optional by using value binding
if let msg = someString {
    println("Message is legit: \(msg)");
} else {
    println("No message");
}

var maybeSomething:String? = "dude, wusup?";
println("\(maybeSomething)");
println("\(maybeSomething!)"); // force unwrap - could be fatal though if nil

// Tuples
// are awesome
let endpoint = ("buy", "POST", 77, 3.14, true);
println("the tuple   => \(endpoint)");
let end0 = endpoint.0;
let end1 = endpoint.1;
let end2 = endpoint.2;
let end3 = endpoint.3;
let end4 = endpoint.4;
println("split tuple => (\(end0), \(end1), \(end2), \(end3), \(end4))");

var endpoint2 = (name: "buy", method: "POST", type: 77, const: 3.14, auth: true);
println("the tuple 2  => \(endpoint2)");
var name   = endpoint2.name;
var method = endpoint2.method;
var type   = endpoint2.type;
var const  = endpoint2.const;
var auth   = endpoint2.auth;
println("split tuple2 => (\(name), \(method), \(type), \(const), \(auth))");
endpoint2.name   = "bart";
endpoint2.method = "PUSH";
endpoint2.type   = 42;
endpoint2.const  = 2.71;
endpoint2.auth   = false;
name   = endpoint2.name;
method = endpoint2.method;
type   = endpoint2.type;
const  = endpoint2.const;
auth   = endpoint2.auth;
println("split tuple3 => (\(name), \(method), \(type), \(const), \(auth))");


// Control Flow
// for loops
for (var i = 0; i < 4; ++i) {
    println("var[] = \(i)");
}

// for-in loops
let nums = ["one", "two", "three", "four"];
for idx in 0..<nums.count {
    let numStr = nums[idx];
    println("[\(idx)]=> \(numStr)");
}

for (idx, numStr) in enumerate(nums) {
    println("Number at index \(idx) is \(numStr)")
}

class Tire { var air = 0; var name = "" }
var tires = [Tire]()
for i in 1...4 {
    tires.append(Tire())
}
println("We have \(tires.count) tires")

var air = 100
for tire in tires {
    tire.air = air
    println("adding air \(air++)")
}

for tire: Tire in tires {
    println("got air: \(tire.air)")
}

var primeList = [2.0]
var num = 3.0
var isPrime = 1
while count(primeList) < 200 {
    var sqrtNum = sqrt(num)
    for primeNumber in primeList {
        if num % primeNumber == 0 {
            isPrime = 0
            break
        }
        if primeNumber > sqrtNum {
            break
        }
    }
    if isPrime == 1 {
        primeList.append(num)
    } else {
        isPrime = 1
    }
    num += 2
}
println("The 200th Prime number is \(primeList[199])")


// switch statements
num = 5
switch num {
    case 2: println("its a two");
    case 3: println("its a three");
    default: println("its something else");
}

num = 5
switch num {
    case 2,3,4: println("its a two, three or four");
    case 5,6: println("its a five or six");
    default: println("its something else");
}

num = 5
switch num {
    case 2...6: println("its a two to six");
    default: println("its something else");
}

// it also works with tuples
var geo = (2,4)
switch geo {
    case (_,5): println("its (something, 5)")
    case (5,_): println("its (5, something)")
    case (1...3,_): println("its (1, 2 or 3, something)")
    case (1...3,3...6): println("its (1, 2 or 3, and 3, 4, 5 or 6)")
    default: println("its something else");
}

// fallthrough
geo = (2,4)
switch geo {
    case (_,5): println("its (something, 5)")
    case (5,_): println("its (5, something)")
    case (1...3,_): println("its (1, 2 or 3, something)")
                    fallthrough
    case (1...3,3...6): println("its (1, 2 or 3, and 3, 4, 5 or 6)")
    default: println("its something else");
}

// value binding
geo = (4,42)
switch geo {
    case (_,5): println("its (something, 5)")
    case (5,_): println("its (5, something)")
    case (1...3,let x): println("its (1, 2 or 3, and \(x))")
    case let (x,y): println("its \(x) and \(y)")
    default: println("its something else");
}

var mystery  = 5
for i in 1...8 {
    if i == mystery {
        break
    }
    println(i)
}

mystery  = 5
for i in 1...8 {
    if i == mystery {
        continue
    }
    println(i)
}

// Labeled statements
mystery  = 5
rangeLoop: for i in 1...8 {
    switch i {
        case mystery:
            println("the mystery number was \(i)")
                break rangeLoop
        case 3:
            println("Was three, not a mystery")
        default:
            println("was some other number \(i)")
    }
    println(i)
}
 
var a = [1,2,3,4];
println("a[0] = \(a[0])");
a[0] = 42;
println("a[0] = \(a[0])");
for i in a {
    println("i = \(i)");
}
for (i,val) in enumerate(a) {
    println("number at \(i) is \(val)");
}

var sprites = [Int](count: 64, repeatedValue: -1)
sprites[0] = 43
sprites[42] = 44
println("sprites[0] = \(sprites[0])");
println("sprites[42] = \(sprites[42])");


func fib_rec(n: Int) -> Int {
    println(n);
    if (n == 0) {
        return 0;
     } 
     if (n == 1) {
           return 1;
     }
     return fib_rec(n - 1) + fib_rec(n - 2);
}

println("fib");
fib_rec(4);


