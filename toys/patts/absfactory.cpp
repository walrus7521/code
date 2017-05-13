#include <iostream>

using namespace std;

class Maze {
};
class Wall {
};
class Room {
public:
    Room(int n) {}
};
class Door {
public:
    Door(Room *r1, Room *r2) {}
};

class MazeFactory {
private:
public:
    MazeFactory(){}

    virtual Maze* MakeMaze() const { return new Maze; }
    virtual Wall* MakeWall() const { return new Wall; }
    virtual Room* MakeRoom(int n) const { return new Room(n); }
    virtual Door* MakeDoor(Room *r1, Room *r2) const { return new Door(r1, r2); }
};

class MazeGame {
public:
    Maze* CreateMaze(MazeFactory& factory) {
        Maze* aMaze = factory.MakeMaze();
        return aMaze;
    }
};

class EnchantedMazeFactory : public MazeFactory {
public:
    EnchantedMazeFactory(){}
    virtual Room* MakeRoom(int n) const {
        return new EnchantedRoom(n); }
    virtual Door* MakeDoor(Room *r1, Room *r2) const {
        return new DoorNeedingStuff(r1, r2); }
};

int main()
{
    MazeGame game;
}
