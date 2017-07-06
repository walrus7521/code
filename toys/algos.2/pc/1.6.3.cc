#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;
 
 
int main()
{
 
    int ns, nstudents;
    double expenses[1000], sum=0, average = 0, deficit, surplus;
 
    while(1) {
        cin >> nstudents;
        if (nstudents == 0) return 0;
 
        sum = average = 0;
        for (ns=0; ns<nstudents; ns++) {
            cin >> expenses[ns]; 
            sum+= expenses[ns];
        }
 
        average = sum / nstudents;
        deficit = surplus = 0;

        for (ns=0; ns<nstudents; ns++) {
            if (expenses[ns] < average) {
                deficit += (floor((average - expenses[ns])*100))/100;
            } else 
            if (expenses[ns] > average) {
                surplus += (floor((-average + expenses[ns])*100))/100;
            }
        }
 
        if (deficit < surplus) {
            deficit = surplus;
        }
        cout << '$' << setprecision(2) << fixed << deficit << endl;
    }
 
    return 0;
}
