#include <iostream>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <valarray>
#include <cmath>
#include "math.h"

void taylor()
{
    double x = 2.0, xn = 1.0, exp_x = 1.0;
    unsigned long fac = 1;
    for (unsigned long i = 1; i <= 10; ++i) {
        xn *= x;
        fac *= i;
        exp_x += xn / fac;
        std::cout << "e^x is " << exp_x << '\n';
    }
}
void collatz(int start)
{
    int x = start;
    while (x != 1) {
        std::cout << x << '\n';
        x = (x % 2 == 1) ? (3 * x + 1) : (x / 2);
        //if (x % 2 == 1) // odd
        //    x = 3 * x + 1;
        //else // even
        //    x = x / 2;
    }
}

void write_something(std::ostream& os)
{
    os << "Hi stream, did you know that 3 * 3 = " << 3 * 3 << std::endl;
}

double dot(const vector& v, const vector& w)
{
    return 3.14;
}

struct cannot_open_file {};
int main()
{
    taylor();
    collatz(19);
    std::cout << "The answer to the Ultimate Question of Life,\n"
        << "the Universe, and Everything is:"
        << std::endl << 6 * 7 << std::endl;

    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
    for (int i : primes)
        std::cout << i << " ";

    // std::cout << "binary: " << 0b11110101 << std::endl;
    try {
        std::fstream f("dude");
        if (!f.is_open())
            throw "dude";  //cannot_open_file{};

    } catch (cannot_open_file& e) {
        std::cout << "dude you suck\n";
    } catch (...) {
    std::cout << "dude you totally suck\n";
    }

    std::ofstream myfile("example.txt");
    std::stringstream mysstream;
    write_something(std::cout);
    write_something(myfile);
    write_something(mysstream);
    std::cout << "mysstream is : " << mysstream.str(); // newline contained

    std::valarray<float> v = { 1, 2, 3 }, w = { 7, 8, 9 }, s = v + 2.0f * w;
    v = sin(s);
    for (float x : v)
        std::cout << x << ' ';
    std::cout << '\n';

    complex z(2.0, 3.0);

    complex z1,     // default-constructed
            z2(),   // default-constructed ????????
            z3(4),  // short for z3(4.0, 0.0)
            z4 = 4, // short for z4(4.0, 0.0)
            z5(0, 1);

    complex x{ z4 };

    complex *p = &x;
    //z.r = 3.5; z.i = 2.0;
    std::cout << "z is(" << *p << ")\n"; // use friend

    double y = dot(3, 4); // illegal with explicit constructor
    std::cout << "y is " << y << '\n';


    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
