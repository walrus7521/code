#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

// alter this to match the csv format
struct data_format {
    std::string name;
    int number;
    double value;
};

data_format deserialize(std::string line)
{
    std::stringstream ss(line); // create a stream of string
    std::string item; // generic string to retrieve individual items
    data_format data; // format structure, see above
    // need to use getline to eliminate the comma
    std::getline(ss, item, ','); data.name   = item;
    std::getline(ss, item, ','); data.number = atoi(item.c_str());
    std::getline(ss, item, ','); data.value  = atof(item.c_str());
    return data;
}

std::string serialize(data_format data)
{
    std::ostringstream ss;
    // serialize individual items to ostringstream
    ss << data.name;   ss << ", "; // append trailing comma
    ss << data.number; ss << ", "; // append trailing comma
    ss << data.value; // no need for trailing comma
    // convert stringstream to string
    std::string line = ss.str();
    return line;
}

std::vector<data_format> csv_in(std::string file)
{
    std::ifstream csv_in(file);
    std::vector<data_format> csv_data;
    std::string line;
    while(getline(csv_in, line)) {
        data_format data = deserialize(line);
        csv_data.push_back(data);
    }
    return csv_data;
}

void csv_out(const std::vector<data_format>& data, std::string file)
{
    std::ofstream csv_out(file);
    for (auto d : data) {
        std::string s = serialize(d);
        csv_out << s << std::endl;
    }
}

void dummy(std::string& s, int& i, double& d)
{
    s += ".sup";
    i += 42;
    d *= 2.0;
}

int main()
{
    std::vector<data_format> data_in = csv_in("testin.csv");
    std::vector<data_format> data_out;
    for (auto d : data_in) {
        dummy(d.name, d.number, d.value);
        data_out.push_back(d); // modified by dummy() function
    }
    csv_out(data_out, "testout.csv");
    return 0;
}

