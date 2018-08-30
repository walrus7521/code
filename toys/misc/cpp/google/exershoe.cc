#include <iostream>

using namespace std;

double pay_salary()
{
    return 600.00;
}

double hourly_plus_comm(double wage, int hours, double commission, int nr_shoes)
{
    double pay = nr_shoes * commission * 225.0;
    pay += wage * hours;

    return pay;
}

double pure_comm(double commission, int nr_shoes)
{
    double pay = nr_shoes * commission * 225.0;
    pay += nr_shoes * 20.0;

    return pay;
}

int main()
{
    int n_shoes_per_week = 20;

    for (int i = 0; i < 20; i++) {
        n_shoes_per_week = i;
        cout << "shoes sold: " << n_shoes_per_week << endl;
        cout << "weekly salary: " << pay_salary() << endl;
        cout << "hourly + salary: " << hourly_plus_comm(7, 40, 0.20, n_shoes_per_week) << endl;
        cout << "pure commmission: " << pure_comm(0.20, n_shoes_per_week) << endl;
    }
}
