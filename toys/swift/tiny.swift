import Foundation
import Cocoa

var map = [  [0,0,0,0,2,0,0,0,0,0],
    [0,1,0,0,0,0,0,0,1,0],
    [0,1,0,0,0,0,0,0,1,0],
    [0,1,0,1,1,1,1,0,1,0],
    [3,0,0,0,0,0,0,0,0,0]]

println("dude, go!")
var currentPoint = (0,4)
func setCurrentPoint() {
    for (i,row) in enumerate(map) {
        for (j,tile) in enumerate(row) {
            if tile == 3 {
                println("here")
                currentPoint = (i,j)
                return
            }
        }
    }
}

setCurrentPoint()
println("ok, you should be good to go now \(currentPoint)")

func moveForward() -> Bool {
    if currentPoint.1 - 1 < 0 {
        println("Off Stage")
        return false
    }
    if isWall((currentPoint.0, currentPoint.1 - 1)) {
        println("Hit Wall")
        return false
    }
    currentPoint.1 -= 1
    if isWin((currentPoint.0, currentPoint.1)) {
        println("You Won!")
    }
    return true
}

func moveBack() -> Bool {
    if currentPoint.1 + 1 > map.count - 1 {
        println("Off Stage")
        return false
    }
    if isWall((currentPoint.0, currentPoint.1 + 1)) {
        println("Hit Wall")
        return false
    }
    currentPoint.1 += 1
    if isWin((currentPoint.0, currentPoint.1)) {
        println("You Won!")
    }
    return true
}

func moveLeft() -> Bool {
    if currentPoint.0 - 1 < 0 {
        return false
    }
    if isWall((currentPoint.0, currentPoint.1)) {
        println("Hit Wall")
        return false
    }
    currentPoint.0 -= 1
    if isWin((currentPoint.0, currentPoint.1)) {
        println("You Won!")
    }
    return true
}

func moveRight() -> Bool {
    if currentPoint.0 + 1 > map.count - 1 {
        println("Off Stage")
        return false
    }
    if isWall((currentPoint.0 + 1, currentPoint.1)) {
        println("Hit Wall")
        return false
    }
    currentPoint.0 += 1
    if isWin((currentPoint.0, currentPoint.1)) {
        println("You Won!")
    }
    return true
}

func isWall(spot:(Int,Int)) -> Bool {
    if map[spot.0][spot.1] == 1 {
        return true
    }
    return false
}

func isWin(spot:(Int,Int)) -> Bool {
    println(spot)
    println(map[spot.0][spot.1])
    if map[spot.0][spot.1] == 2 {
        return true
    }
    return false
}

println("hello, dude")

moveRight()
moveLeft()
moveLeft()
moveLeft()
moveForward()
moveBack()
moveLeft()
moveLeft()


