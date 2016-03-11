#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

using namespace std;

#define HI_NUM 100

int main ()
{
  int iSecret, iGuess;

  /* initialize random seed: */
  srand (time(NULL));

  /* generate secret number between 1 and HI_NUM: */
  iSecret = rand() % HI_NUM + 1;

  do {
    cout <<  "Guess the number (1 to " << HI_NUM << "): ";

    if (!(cin >> iGuess)) {
      cout << "You entered a non-numeric. Recovering ..." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      continue;
    }
 
    if (iSecret < iGuess) cout << "The secret number is lower" << endl;
    else if (iSecret > iGuess) cout << "The secret number is higher" << endl;
  } while (iSecret != iGuess);

  cout << "Congratulations!" << endl;
  return 0;
}
