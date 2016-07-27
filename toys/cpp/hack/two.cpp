#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int test()
{
    double meal_cost;
    int tip_percent;
    int tax_percent;
    int total_meal_cost;

    cin >> meal_cost; 
    cin >> tip_percent; 
    cin >> tax_percent; 

    tip_percent = round(meal_cost * tip_percent/100);
    tax_percent = round(meal_cost *  tax_percent/100);
    total_meal_cost = meal_cost + tip_percent + tax_percent;

    cout << "The total meal cost is " << total_meal_cost << " dollars.";

}

int main() {
    test();
    return 0;

    double meal_cost;
    int total_meal_cost;
    int tip_percent;
    int tax_percent;
    double tip, tax;
   
    cin >> meal_cost;
    cin >> tip_percent;
    cin >> tax_percent;

    cout << "meal cost  : " << meal_cost << endl;
    cout << "tip percent: " << tip_percent << endl;
    cout << "tax percent: " << tax_percent << endl;
    
    tip = meal_cost * ((double) tip_percent / 100.0);
    tax = meal_cost * ((double) tax_percent / 100.0);
    meal_cost = meal_cost + tip + tax;
    total_meal_cost = (int) (meal_cost + 0.5);

    cout << "tip        : " << tip << endl;
    cout << "tax        : " << tax << endl;
    cout << "meal cost  : " << meal_cost << endl;

    cout << "The total meal cost is " << total_meal_cost << endl;

    return 0;
}
