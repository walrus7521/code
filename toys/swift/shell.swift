#!/usr/bin/swift

#!/usr/bin/swift-im

//#!/usr/bin/env xcrun swift

//# execute using: 
//# chmod +x shell.swift
//# ./shell.swift -- one two three four
//#    or
//# ./shell.swift one two three four
 
var argc = Process.arguments.count
println("num args: \(argc)")

println("Process.arguments gave args:")
for s in Process.arguments {
  println(s)
  switch (s) {
      case "one":   println("yo 1")
      case "two":   println("yo 2")
      case "three": println("yo 3")
      case "four":  println("yo 4")
      default: println("sup")
  }
}

