#include <iostream>
#include <octave/oct.h>

// mkoctfile --link-stand-alone standalone.cc -o standalone

using namespace std;

int main ()
{

  Complex number = Complex(0, 1);
  cout << number;

  //loan(32,.1,.10);

}

