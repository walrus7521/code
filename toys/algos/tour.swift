https://developer.apple.com/swift/

Collections: arrays, dictionaries and sets

Array:
    var iarray: Array<Int>
    var iarray: [Int]
    let iarray = [1,2,3]

Dict:
    var dict: Dictionary<String, Int>
    var dict: [String, Int]
    let viet = ["hanoi":7, "saigon":8]

Set:
    var set: Set<Int>

Initializers:
    let str = String()          // ""
    let iarray = [Int]()        // 0 elements
    let set = Set<Float>()      // 0 elements
    Int()                       // 0
    Bool()                      // false
    String)7)
    Set([1,2,3])
    Float(3.14)

Properties:
    String.isEmpty()
    Array<T>.count

Methods:
    Array<T>.append(_:)
    String.append("val")
    Dict.enumerated() returns tuples of key value pairs
    Enum.rawValue // gives actual value of enum

Optionals: // may not store any value => nil
    var opFlt: Float?
    optionals must be unwrapped, not just read due to possibly being nil
    2 ways: forced with !, binding if-let/else

Subscripting dictionaries:
    for non-existent entries, nil is returned so use if-let/else

Loops and string interpolation:
    Range for: for i in range {}
    for (city, num) in viet {}
    String interpolation: let s = "City \(city): Code \(num)"

Enums and Switch
    Enums can be Int, Float, String, Character 
