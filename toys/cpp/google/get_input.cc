// get_input.cpp: Maggie Johnson
// Description: Illustrate the use of cin to get input.
/*
 *
 * An experiment:
 *
 * When an input error is made, the stream "breaks," cin returns false, 
 * and the program stops. It's very important to guard against such 
 * errors as we did in the program above. But what if we want to recover 
 * from the error, rather than have the program stop? There are two steps 
 * to recovering from an error:
 * Clear the error with cin.clear().
 * Remove the incorrect characters from the stream. One way to do this is 
 * with cin.ignore().
 * Write a program that recovers from bad input using these two steps. 
 * Use Google to search for how these methods work. Our solution is here.
 *
 */

#include <iostream>
using namespace std;

int main() {
  int input_var = 0;
  // Enter the do while loop and stay there until either
  // a non-numeric is entered, or -1 is entered. Note that
  // cin will accept any integer, 4, 40, 400, etc.
  do {
    cout << "Enter a number (-1 = quit): ";
    // The following line accepts input from the keyboard into
    // variable input_var.
    // cin returns false if an input operation fails, that is, if
    // something other than an int (the type of input_var) is entered.
    if (!(cin >> input_var)) {
      cout << "You entered a non-numeric. Exiting..." << endl;
      break;
      // exit the do while loop
    }
    if (input_var != -1) {
      cout << "You entered " << input_var << endl;
    }
  } while (input_var != -1);
  cout << "All done." << endl;
  return 0;
}

