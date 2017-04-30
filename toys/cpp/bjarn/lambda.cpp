#include <chrono> 
#include <iostream> 

// https://tatourian.com/2013/03/26/producer-consumer-inter-thread-communication-using-condition-variables-in-c/

using namespace std;

//typedef (*[]()->void) ftype;

typedef std::function<void(int&)> f1;
typedef std::function<int(int)> f2;
typedef std::function<float(int,int)> f3;

int main() 
{ 
    int bacon = 42;

    auto f = [&bacon]()->void { std::cout << "dbagger: " << bacon << std::endl; bacon = 47; };
    f(); // calling the lambda

    std::cout << "bacon: " << bacon << std::endl;

    return 0; 
}

