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

class Singleton
{
    public:
        static Singleton& getInstance() {
            static Singleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }
    private:
        Singleton() {}; // Constructor? (the {} brackets) are needed here.
        // C++ 03
        // ========
        // Dont forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        Singleton(Singleton const&);      // Don't Implement
        void operator=(Singleton const&); // Don't implement
        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        //S(S const&)               = delete;
        //void operator=(S const&)  = delete;
};

int main() {
    return 0;
}

