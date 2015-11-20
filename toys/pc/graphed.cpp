#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
 
/*
 * create a singleton class to implement these methods
 *
  I M N   Create a new M x N image with all pixels initially colored white (O).
  C   Clear the table by setting all pixels white (O). The size remains unchanged.
  L X Y C Colors the pixel (X, Y) in color (C).
  V X Y1 Y2 C Draw a vertical segment of color (C) in column X, between the rows Y1 and Y2 inclusive.
  H X1 X2 Y C Draw a horizontal segment of color (C) in the row Y, between the columns X1 and X2 inclusive.
  K X1 Y1 X2 Y2 C Draw a filled rectangle of color C, where (X1, Y1) is the upper-left and (X2, Y2) the lower right corner.
  F X Y C Fill the region R with the color C, where R is defined as follows. Pixel (X, Y) belongs to R. Any other pixel which is the same color as pixel (X, Y) and shares a common side with any pixel in R also belongs to this region.
  S Name  Write the file name in MSDOS 8.3 format followed by the contents of the current image.
  X   Terminate the session.
*/


using namespace std;

class GraphEd {
public:
    static GraphEd& getInstance() {
        static GraphEd instance;
        return instance;
    }
    void create(int rows, int cols) { 
        Rows = rows; Cols = cols;
        Grid = (char**) calloc(Rows+1, sizeof(char*));  
        for (int r = 0; r <= Rows; r++) {
            Grid[r] = (char*) calloc(Cols+1, sizeof(char));
        }
        for (int r = 0; r <= Rows; r++) {
            for (int c = 0; c <= Cols; c++) {
                Grid[r][c] = 'o';
            }
        }
    }
    void clear() { 
        for (int r = 0; r <= Rows; r++) {
            for (int c = 0; c <= Cols; c++) {
                Grid[r][c] = 'o';
            }
        }
    }
    void fill(int row, int col, char color) {
        /* find connected regions:
         * Fill the region
         
         */
        cout << "fill: " << row << " to " << col << " color=" << color << endl;
    }
    void horz(int row, int col1, int col2, char color)  { 
        for (int c = col1; c <= col2; ++c) {
            Grid[row][c] = color;
        }
    }
    void vert(int row1, int row2, int col, char color)  { 
        for (int r = row1; r <= row2; ++r) {
            Grid[r][col] = color;
        }
    }
    void rect(int row1, int row2, int col1, int col2, char color)  { 
        for (int r = row1; r <= row2; ++r) {
            for (int c = col1; c <= col2; ++c) {
                Grid[r][c] = color;
            }
        }
    }
    void color(int row, int col, char color) { 
        Grid[row][col] = color;
    }
    void write(string name) { 
        Name = name; cout << "write: " << Name << endl; 
    }
    void show(string name) {
        cout << name << endl;
        for (int r = 1; r <= Rows; r++) {
            for (int c = 1; c <= Cols; c++) {
                cout << Grid[r][c];
            }
            cout << endl;
        }
    }
    void terminate() { 
    }
private:
    GraphEd() {};
    void operator=(GraphEd const&);
    string Name;
    int Rows, Cols;
    char **Grid;
};

int main() {
    string line, Name;
    int rows, cols, row, row1, row2, col, col1, col2;
    char color, cmd, name[64];

    GraphEd ged = GraphEd::getInstance();

    while (getline(cin, line)) {
        stringstream in(line);
        //cout << "got line: " << line << endl;
        switch (line[0]) {
            case 'C':
                // C   Clear the table by setting all pixels white (O). The size remains unchanged.
                ged.clear();
                break;
            case 'F':
                // F x y C Fill the region R with the color C, where R is defined as follows. 
                // Pixel (x, y) belongs to R. Any other pixel which is the same color as 
                // pixel (x, y) and shares a common side with any pixel in R also belongs to this region.
                sscanf(line.c_str(), "%c %d %d %c\n", &cmd, &col, &row, &color);
                ged.fill(row, col, color);
                break;
            case 'H':
                // H x1 x2 y C Draw a horizontal segment of color (C) in the row y, between 
                // the columns x1 and x2 inclusive.
                sscanf(line.c_str(), "%c %d %d %d %c\n", &cmd, &col1, &col2, &row, &color);
                ged.horz(row, col1, col2, color);
                break;
            case 'I': 
                // I M=cols N=rows Create a new M x N image with all pixels initially colored white (O).
                sscanf(line.c_str(), "%c %d %d\n", &cmd, &cols, &rows);
                ged.create(rows, cols);
                break;
            case 'K':
                // K x1 y1 x2 y2 c Draw a filled rectangle of color c, where (x1, y1) is the 
                // upper-left and (x2, y2) the lower right corner.
                sscanf(line.c_str(), "%c %d %d %d %d %c\n", &cmd, &col1, &row1, &col2, &row2, &color);
                ged.rect(row1, row2, col1, col2, color);
                break;
            case 'L':
                // L x y c Colors the pixel (x, y) in color (c).
                sscanf(line.c_str(), "%c %d %d %c\n", &cmd, &col, &row, &color);
                ged.color(row, col, color);
                break;
            case 'S':
                // S Name  Write the file name in MSDOS 8.3 format followed by the contents of the current image.
                sscanf(line.c_str(), "%c %s\n", &cmd, name);
                Name = name;
                ged.show(Name);
                break;
            case 'V':
                // V x y1 y2 c Draw a vertical segment of color (c) in column x, between the rows y1 and y2 inclusive.
                sscanf(line.c_str(), "%c %d %d %d %c\n", &cmd, &col, &row1, &row2, &color);
                ged.vert(row1, row2, col, color);
                break;
            case 'X':
                // X   Terminate the session.
                ged.terminate();
                goto end;
                break;
        }
    }
end:
    return 0;
}

