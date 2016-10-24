#!/usr/bin/swift

// https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/GuidedTour.html
// http://swiftable.io/2016/06/dispatch-queues-swift-3/


print("Hello")

let countingUp = ["one", "two"]

for s in countingUp {
    let str = s
    print(str)
}

let individualScores = [75, 43, 103, 87, 12]
var teamScore = 0
for score in individualScores {
    if score > 50 {
        teamScore += 3
    } else {
        teamScore += 1
    }
}
print(teamScore)

// next
print("next");
var optionalString: String? = "Hello"
print(optionalString == nil)
var optionalName: String? = "John Appleseed"
var greeting = "Hello!"
if let name = optionalName {
    greeting = "Hello, \(name)"
}

print("switch")
let vegetable = "red pepper"
switch vegetable {
case "celery":
    print("Add some raisins and make ants on a log.")
case "cucumber", "watercress":
    print("That would make a good tea sandwich.")
case let x where x.hasSuffix("pepper"):
    print("Is it a spicy \(x)?")
default:
    print("Everything tastes good in soup.")
}

print("for-in")
let interestingNumbers = [
    "Prime": [2, 3, 5, 7, 11, 13],
    "Fibonacci": [1, 1, 2, 3, 5, 8],
    "Square": [1, 4, 9, 16, 25],
]
var largest = 0
for (kind, numbers) in interestingNumbers {
    for number in numbers {
        if number > largest {
            largest = number
        }
    }
}
print(largest)

print("func")
func greet(person: String, day: String) -> String {
    return "Hello \(person), today is \(day)."
}
print(greet(person: "Bob", day: "Tuesday"))

print("tuple")
func calculateStatistics(scores: [Int]) -> (min: Int, max: Int, sum: Int) {
    var min = scores[0]
    var max = scores[0]
    var sum = 0
    
    for score in scores {
        if score > max {
            max = score
        } else if score < min {
            min = score
        }
        sum += score
    }
    
    return (min, max, sum)
}
let statistics = calculateStatistics(scores: [5, 3, 100, 3, 9])
print(statistics.sum)
print(statistics.2)

print("variadic funcs")
func sumOf(numbers: Int...) -> Int {
    var sum = 0
    for number in numbers {
        sum += number
    }
    return sum
}
print(sumOf())
print(sumOf(numbers: 42, 597, 12))

print("nested funcs")
func returnFifteen() -> Int {
    var y = 10
    func add() {
        y += 5
    }
    add()
    return y
}
print(returnFifteen())

print("closure")
func makeIncrementer() -> ((Int) -> Int) {
    func addOne(number: Int) -> Int {
        return 1 + number
    }
    return addOne
}
var increment = makeIncrementer()
print(increment(7))

print("closure 2")
func hasAnyMatches(list: [Int], condition: (Int) -> Bool) -> Bool {
    for item in list {
        if condition(item) {
            return true
        }
    }
    return false
}
func lessThanTen(number: Int) -> Bool {
    return number < 10
}
var numbers = [20, 19, 7, 12]
print(hasAnyMatches(list: numbers, condition: lessThanTen))

print("closure 3")
numbers.map({
    (number: Int) -> Int in
    let result = 3 * number
    return result
})
let mappedNumbers = numbers.map({ number in 3 * number })
print(mappedNumbers)
let sortedNumbers = numbers.sorted { $0 > $1 }
print(sortedNumbers)


print("objects, classes")
class Shape {
    var numberOfSides = 0
    func simpleDescription() -> String {
        return "A shape with \(numberOfSides) sides."
    }
}
var shape = Shape()
shape.numberOfSides = 7
var shapeDescription = shape.simpleDescription()

class NamedShape {
    var numberOfSides: Int = 0
    var name: String
    
    init(name: String) {
        self.name = name
    }
    
    func simpleDescription() -> String {
        return "A shape with \(numberOfSides) sides."
    }
}


print("enum")
enum Suit {
    case spades, hearts, diamonds, clubs
    func simpleDescription() -> String {
        switch self {
        case .spades:
            return "spades"
        case .hearts:
            return "hearts"
        case .diamonds:
            return "diamonds"
        case .clubs:
            return "clubs"
        }
    }
}
let hearts = Suit.hearts
let heartsDescription = hearts.simpleDescription()
print(hearts)
print(heartsDescription)

print("struct")
enum Rank: Int {
    case ace = 1
    case two, three, four, five, six, seven, eight, nine, ten
    case jack, queen, king
    func simpleDescription() -> String {
        switch self {
        case .ace:
            return "ace"
        case .jack:
            return "jack"
        case .queen:
            return "queen"
        case .king:
            return "king"
        default:
            return String(self.rawValue)
        }
    }
}
let ace = Rank.ace
let aceRawValue = ace.rawValue

struct Card {
    var rank: Rank
    var suit: Suit
    func simpleDescription() -> String {
        return "The \(rank.simpleDescription()) of \(suit.simpleDescription())"
    }
}
let threeOfSpades = Card(rank: .three, suit: .spades)
let threeOfSpadesDescription = threeOfSpades.simpleDescription()
print(threeOfSpades)


print("protocol")
protocol ExampleProtocol {
    var simpleDescription: String { get }
    mutating func adjust()
}
class SimpleClass: ExampleProtocol {
    var simpleDescription: String = "A very simple class."
    var anotherProperty: Int = 69105
    func adjust() {
        simpleDescription += "  Now 100% adjusted."
    }
}
var a = SimpleClass()
a.adjust()
let aDescription = a.simpleDescription
 
struct SimpleStructure: ExampleProtocol {
    var simpleDescription: String = "A simple structure"
    mutating func adjust() {
        simpleDescription += " (adjusted)"
    }
}
var b = SimpleStructure()
b.adjust()
let bDescription = b.simpleDescription
extension Int: ExampleProtocol {
    var simpleDescription: String {
        return "The number \(self)"
    }
    mutating func adjust() {
        self += 42
    }
}
print(7.simpleDescription)
let protocolValue: ExampleProtocol = a
print(protocolValue.simpleDescription)
// print(protocolValue.anotherProperty)  // Uncomment to see the error

print("error handling")
enum PrinterError: Error {
    case outOfPaper
    case noToner
    case onFire
}
func send(job: Int, toPrinter printerName: String) throws -> String {
    if printerName == "Never Has Toner" {
        throw PrinterError.noToner
    }
    return "Job sent"
}
do {
    let printerResponse = try send(job: 1040, toPrinter: "Bi Sheng")
    print(printerResponse)
} catch {
    print(error)
}

print("try-catch")
do {
    let printerResponse = try send(job: 1440, toPrinter: "Gutenberg")
    print(printerResponse)
} catch PrinterError.onFire {
    print("I'll just put this over here, with the rest of the fire.")
} catch let printerError as PrinterError {
    print("Printer error: \(printerError).")
} catch {
    print(error)
}
let printerSuccess = try? send(job: 1884, toPrinter: "Mergenthaler")
let printerFailure = try? send(job: 1885, toPrinter: "Never Has Toner")

print("defer")
var fridgeIsOpen = false
let fridgeContent = ["milk", "eggs", "leftovers"]
 
func fridgeContains(_ food: String) -> Bool {
    fridgeIsOpen = true
    defer {
        fridgeIsOpen = false
    }
    
    let result = fridgeContent.contains(food)
    return result
}
fridgeContains("banana")
print(fridgeIsOpen)

print("generics")
func makeArray<Item>(repeating item: Item, numberOfTimes: Int) -> [Item] {
    var result = [Item]()
    for _ in 0..<numberOfTimes {
        result.append(item)
    }
    return result
}
makeArray(repeating: "knock", numberOfTimes:4)
// Reimplement the Swift standard library's optional type
enum OptionalValue<Wrapped> {
    case none
    case some(Wrapped)
}
var possibleInteger: OptionalValue<Int> = .none
possibleInteger = .some(100)

print("where")
func anyCommonElements<T: Sequence, U: Sequence>(_ lhs: T, _ rhs: U) -> Bool
    where T.Iterator.Element: Equatable, T.Iterator.Element == U.Iterator.Element {
        for lhsItem in lhs {
            for rhsItem in rhs {
                if lhsItem == rhsItem {
                    return true
                }
            }
        }
        return false
}
print(anyCommonElements([1, 2, 3], [3]))


print("concurrency")
import Foundation
import Dispatch
//import UIKit
let queue = DispatchQueue(label: "com.app.queue")
let serialQueue = DispatchQueue(label: "queuename")
//serialQueue.sync { 
//    print("Dispatched to background queue")    
//}
//DispatchQueue.main.async {
//    print("main thread dispatch")        
//}
//DispatchQueue.global(qos: .userInitiated).async {
//    print("user initiated task")
//}
//DispatchQueue.global(attributes: .qosDefault).async {
//}
let block = DispatchWorkItem {
    print("do something")
}
DispatchQueue.main.async(execute: block)



//let qosClass = QOS_CLASS_BACKGROUND
//let backgroundQueue = dispatch_get_global_queue(qosClass, 0)
//dispatch_async(backgroundQueue, {
//    print("Work on background queue")
//})

//DispatchQueue.global(attributes: [.qosDefault]).async { 
//    // Background thread
//    DispatchQueue.main.async(execute: { 
//        // UI Updates
//    })
//}

//let queue = DispatchQueue.global(attributes: .qosUserInitiated)
let mainQueue = DispatchQueue.main

//mainQueue.async {
//    dispatchPrecondition(condition: .notOnQueue(mainQueue))
//    // This code won't execute
//}

//queue.async {
//    dispatchPrecondition(condition: .onQueue(queue))
//    // This code will execute
//}






