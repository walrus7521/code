#include <stdio.h>
#include "CTest_stub.h"

int main (int argc, char *argv[]) {
  hs_init(&argc, &argv);
  printf("%s\n", hello());
  hs_exit();
  return 0;
}

/*

$ ghc CTest
[1 of 1] Compiling CTest            ( CTest.hs, CTest.o )
$ ghc -o ctest ctest.c CTest.o -no-hs-main
$ ./ctest

https://stackoverflow.com/questions/17812166/how-to-pass-a-string-from-haskell-to-c
 */
