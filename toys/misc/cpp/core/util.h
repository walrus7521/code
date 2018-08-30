#include <iostream>

class UtilApi
{
public:
    UtilApi() = delete;

    static bool Check() { return true; };
    static bool Check(const std::string & file) { std::cout << file << std::endl; return false; };

private:
    static const std::string DEFAULT_UTIL_EXTENSION;

};

