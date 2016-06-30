// unordered_set::emplace
#include <iostream>
#include <string>
#include <set>
//#include <unordered_set>

void doset()
{
    std::set<int>::iterator it;
    int myints[] = {1,2,3,4,5};
    std::set<int> myset(myints, myints+5);
    for (it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
}

int main ()
{
    doset();
    //std::unordered_set<std::string> myset;
    std::set<std::string> myset;
    std::set<std::string>::iterator it;

    myset.insert ("potatoes");
    myset.insert ("milk");
    myset.insert ("flour");
    //myset.emplace ("potatoes");
    //myset.emplace ("milk");
    //myset.emplace ("flour");

    std::cout << "myset contains:";
    //for (const std::string& x: myset) std::cout << " " << x;
    for (it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << std::endl;
    return 0;
}
