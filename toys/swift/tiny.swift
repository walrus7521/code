import Foundation
import Cocoa

var map = [  [0,0,0,0,2,0,0,0,0,0],
    [0,1,0,0,0,0,0,0,1,0],
    [0,1,0,0,0,0,0,0,1,0],
    [0,1,0,1,1,1,1,0,1,0],
    [3,0,0,0,0,0,0,0,0,0]]

print("dude, go!")
var currentPoint = (0,4)
func setCurrentPoint() {
    for (i,row) in map.enumerate() {
        for (j,tile) in row.enumerate() {
            if tile == 3 {
                print("here")
                currentPoint = (i,j)
                return
            }
        }
    }
}

setCurrentPoint()
print("ok, you should be good to go now \(currentPoint)")

func moveForward() -> Bool {
    if currentPoint.1 - 1 < 0 {
        print("Off Stage")
        return false
    }
    if isWall((currentPoint.0, currentPoint.1 - 1)) {
        print("Hit Wall")
        return false
    }
    currentPoint.1 -= 1
    if isWin((currentPoint.0, currentPoint.1)) {
        print("You Won!")
    }
    return true
}

func moveBack() -> Bool {
    if currentPoint.1 + 1 > map.count - 1 {
        print("Off Stage")
        return false
    }
    if isWall((currentPoint.0, currentPoint.1 + 1)) {
        print("Hit Wall")
        return false
    }
    currentPoint.1 += 1
    if isWin((currentPoint.0, currentPoint.1)) {
        print("You Won!")
    }
    return true
}

func moveLeft() -> Bool {
    if currentPoint.0 - 1 < 0 {
        return false
    }
    if isWall((currentPoint.0, currentPoint.1)) {
        print("Hit Wall")
        return false
    }
    currentPoint.0 -= 1
    if isWin((currentPoint.0, currentPoint.1)) {
        print("You Won!")
    }
    return true
}

func moveRight() -> Bool {
    if currentPoint.0 + 1 > map.count - 1 {
        print("Off Stage")
        return false
    }
    if isWall((currentPoint.0 + 1, currentPoint.1)) {
        print("Hit Wall")
        return false
    }
    currentPoint.0 += 1
    if isWin((currentPoint.0, currentPoint.1)) {
        print("You Won!")
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
    print(spot)
    print(map[spot.0][spot.1])
    if map[spot.0][spot.1] == 2 {
        return true
    }
    return false
}

print("hello, dude")

moveRight()
moveLeft()
moveLeft()
moveLeft()
moveForward()
moveBack()
moveLeft()
moveLeft()


