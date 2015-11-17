#include <tuple>
#include <iostream>
#include "blob.h"
#include <string>
#include <vector>

std::vector<field_type> ftv = { 
    std::make_tuple(0, 2, std::string("Sec Version")),
    std::make_tuple(2, 2, std::string("Checksum")),
    std::make_tuple(4, 2, std::string("Q Block Start")),
    std::make_tuple(6, 2, std::string("L Block Subsections")),
    std::make_tuple(8, 4, std::string("L Block Sub #1 Offset")),
    std::make_tuple(12, 4, std::string("L Block Sub #1 Size")),
    std::make_tuple(16, 4, std::string("L Block Sub #2 Offset")),
    std::make_tuple(20, 4, std::string("L Block Sub #2 Size")),
    std::make_tuple(24, 4, std::string("L Block Sub #3 Offset")),
    std::make_tuple(28, 4, std::string("L Block Sub #3 Size")),
    std::make_tuple(32, 4, std::string("L Block Sub #4 Offset")),
    std::make_tuple(36, 4, std::string("L Block Sub #4 Size"))
};

int main() {
    Blob b(ftv);
    for (std::vector<field_type>::const_iterator i = b.fields.begin(); i != b.fields.end(); ++i) {
        std::cout << "size:   " << std::get<0>(*i) << std::endl;
        std::cout << "offset: " << std::get<1>(*i) << std::endl;
        std::cout << "name:   " << std::get<2>(*i) << std::endl;
    }
    return 0;
}
