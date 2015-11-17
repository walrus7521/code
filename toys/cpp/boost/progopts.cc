#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char *argv[]) 
{
#if 0
    opt::options_description desc("All options");
    desc.add_options()
        ("apples,a", opt::value<int>()->default_value(10),
            "apples that you have")
        ("oranges,o", opt::value<int>(), "oranges that you have")
        ("name", opt::value<std::string>(), "your name")
        ("help", "produce help message");
    opt::variables_map vm;
#endif

}

