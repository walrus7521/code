#include "pch.hpp"
#include "Csv.hpp"

int main()
{
    std::vector<data_format> data_in = csv_in<data_format>("testin.csv");
    std::vector<data_format> data_out;
    for (auto d : data_in) {
        //dummy(d.name, d.number, d.value);
        data_out.push_back(d); // modified by dummy() function
    }
    csv_out<data_format>(data_out, "testout.csv");
    return 0;
}
