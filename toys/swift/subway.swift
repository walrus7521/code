//: Playground - noun: a place where people can play

import Cocoa
import Foundation

let city = "Boston"
let trainName = "the Red Line"

var subwayStops = [
    // Stop name nad busyness on scale 1-10
    ("Harvard Square", 6),
    ("Kendall", 5),
    ("Central Square", 7),
    ("Charles MGH", 4),
    ("Park Street", 10)
]

var passengers = 0
for i in 0..<subwayStops.count {
    var (stopName, busyness) = subwayStops[i]
    var board:Int
    
    switch (busyness) {
    case 1...4: board = 15
    case 5...7: board = 30
    case 7..<9: board = 45
    case 10: board = 50
    default: board = 0
    }
    
    // Some passengers may leave the train at each stop
    let randomNumber = Int(arc4random_uniform(UInt32(passengers)))
    // Ensure that passengers never becomes negative
    if randomNumber < passengers {
        passengers -= randomNumber
        println("\(randomNumber) leave the train")
    }
    
    passengers += board
    println("\(board) new passengers board at \(stopName)")
    println("\(passengers) current on board")
    
}
println("A total of \(passengers) passengers were left on \(trainName) in \(city)")



