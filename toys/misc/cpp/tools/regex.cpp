#include <iostream>
#include <string>
#include <regex>

int main ()
{
    std::string str("1231xbart");
    std::regex r("^(\\d+)x(\\w+)");
    std::smatch m;
    std::regex_search(str, m, r);
    for(auto v: m) std::cout << v << std::endl;
}

