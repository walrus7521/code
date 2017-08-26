#include <iostream>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::vector;
using std::array;

struct Coordinate {
    bool operator==(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
};

bool IsFeasible(const Coordinate& cur, const vector<vector<int>>& maze) {
    return cur.x >= 0 && cur.x < maze.size() && cur.y >= 0 &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == 0;
}

bool SearchMazeHelper(const Coordinate& cur, const Coordinate& e,
        vector<vector<int>>* maze, vector<Coordinate>* path) {

    if (cur == e) {
        return true;
    }

    const array<array<int, 2>, 4> shift = {
        {{{0,1}}, {{0, -1}}, {{1,0}}, {{-1,0}}}};

    for (const auto& s : shift) {
        Coordinate next{cur.x + s[0], cur.y + s[1]};
        if (IsFeasible(next, *maze)) {
            (*maze)[next.x][next.y] = 1;
            path->emplace_back(next);
            if (SearchMazeHelper(next, e, maze, path)) {
                return true;
            }
            path->pop_back();
        }
    }
    return false;
}

vector<Coordinate> SearchMaze(vector<vector<int>> maze, const Coordinate& s, const Coordinate& e) {
    vector<Coordinate> path;
    maze[s.x][s.y] = 1;
    path.emplace_back(s);
    if (!SearchMazeHelper(s, e, &maze, &path)) {
        path.pop_back();
    }
    return path;
}

int maze_size_y = 10, maze_size_x = 10;
void show(vector<vector<int>>& maze) {
    for (size_t y=0;y<maze_size_y;y++) {
        for (size_t x=0;x<maze_size_x;x++) { 
            if (maze[y][x]==1) 
                printf("#"); 
            else 
                printf("."); 
        }
        cout << endl;
    }
}

void init(vector<vector<int>>& maze) {
    maze.resize(maze_size_y); 
    for (size_t y=0;y<maze_size_y;y++) 
        maze[y].resize(maze_size_x); 
 
    for (size_t x=0;x<maze_size_x;x++) 
        for (size_t y=0;y<maze_size_y;y++) 
            maze[y][x]=0; 
    maze[0][0] = 1;
    maze[2][0] = 1;
    maze[7][0] = 1;
    maze[8][0] = 1;
    maze[4][1] = 1;
    maze[5][1] = 1;
    maze[1][2] = 1;
    maze[2][2] = 1;
    maze[4][2] = 1;
    maze[5][2] = 1;
    maze[7][2] = 1;
    maze[8][2] = 1;
    maze[3][3] = 1;
    maze[8][3] = 1;
    maze[3][4] = 1;
    maze[6][4] = 1;
    maze[7][4] = 1;
    maze[2][5] = 1;
    maze[3][5] = 1;
    maze[5][5] = 1;
    maze[0][6] = 1;
    maze[2][6] = 1;
    maze[7][6] = 1;
    maze[0][7] = 1;
    maze[5][7] = 1;
    maze[8][7] = 1;
    maze[9][7] = 1;
    maze[2][8] = 1;
    maze[3][8] = 1;
    maze[5][8] = 1;
    maze[8][8] = 1;
    maze[9][8] = 1;
    maze[2][9] = 1;
    maze[8][9] = 1;
}


int main()
{
    vector<vector<int>> maze; // = {{1,2}, {3,4}};
    init(maze);
    show(maze);
    //return 0;
    Coordinate s = {9,0}, e = {0,9};
    vector<Coordinate> path = SearchMaze(maze, s, e);
    for (Coordinate c : path) {
        cout << "[x] = " << c.x << "[y] = " << c.y << endl;
    }
    return 0;
}

/**

#.....##..
..#.......
#.#..##.##
...###..#.
.##.......
.##..#.##.
....#.....
#.#.#.#...
#.##...###
.......##.

[x] = 9[y] = 0
[x] = 9[y] = 1
[x] = 9[y] = 2
[x] = 9[y] = 3
[x] = 9[y] = 4
[x] = 9[y] = 5
[x] = 9[y] = 6
[x] = 8[y] = 6
[x] = 8[y] = 5
[x] = 7[y] = 5
[x] = 6[y] = 5
[x] = 6[y] = 6
[x] = 6[y] = 7
[x] = 6[y] = 8
[x] = 6[y] = 9
[x] = 5[y] = 9
[x] = 4[y] = 9
[x] = 4[y] = 8
[x] = 4[y] = 7
[x] = 4[y] = 6
[x] = 4[y] = 5
[x] = 4[y] = 4
[x] = 4[y] = 3
[x] = 5[y] = 3
[x] = 6[y] = 3
[x] = 6[y] = 2
[x] = 6[y] = 1
[x] = 6[y] = 0
[x] = 5[y] = 0
[x] = 4[y] = 0
[x] = 3[y] = 0
[x] = 3[y] = 1
[x] = 2[y] = 1
[x] = 1[y] = 1
[x] = 0[y] = 1
[x] = 0[y] = 2
[x] = 0[y] = 3
[x] = 0[y] = 4
[x] = 0[y] = 5
[x] = 1[y] = 5
[x] = 1[y] = 6
[x] = 1[y] = 7
[x] = 1[y] = 8
[x] = 1[y] = 9
[x] = 0[y] = 9

**/

