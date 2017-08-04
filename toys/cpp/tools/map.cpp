#include <iostream>
#include <string>
#include <unordered_map>


void test()
{
    std::unordered_map<std::string,int> mymap2;

    mymap2.insert(std::make_pair<std::string,double>("eggs", 42));
    auto p = std::make_pair<std::string,double>("bacon", 82);
    mymap2.insert(p);

    mymap2["eggs"] += 1;
    mymap2["bacon"] += 2;

    for (auto& x: mymap2) {
        std::cout << x.first << ": " << x.second << std::endl;
    }
}


int main ()
{
    std::unordered_map<std::string,int> mymap = {
                  { "Mars", 3000},
                  { "Saturn", 60000},
                  { "Jupiter", 70000 } };

    //mymap.at("Mars") = 3396;
    //mymap.at("Saturn") += 272;
    //mymap.at("Jupiter") = mymap.at("Saturn") + 9638;

    mymap["Mars"] = 3396;
    mymap["Saturn"] += 272;
    mymap["Jupiter"] = mymap["Saturn"] + 9638;


    for (auto& x: mymap) {
        std::cout << x.first << ": " << x.second << std::endl;
    }

    test();

    return 0;
}
