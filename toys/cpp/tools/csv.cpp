#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

enum types
{
    u8_type,
    u16_type,
    u32_type,
    U64_type,
    s8_type,
    s16_type,
    s32_type,
    s64_type,
    f32_type,
    bool_type
};

// alter this to match the csv format
struct data_format {
    string name;
    int number;
    double value;
};

data_format deserialize(string line)
{
    std::stringstream ss(line); // create a stream of string
    string item;
    data_format data;

    // need to use getline to delete the comma
    std::getline(ss, item, ','); data.name   = item;
    std::getline(ss, item, ','); data.number = atoi(item.c_str());
    std::getline(ss, item, ','); data.value  = atof(item.c_str());

    return data;
}

string serialize(data_format data)
{
    std::ostringstream ss;
    std::ostringstream name, number, value;

    name   << data.name;
    number << data.number;
    value  << data.value;
    ss << name.str() << ", " << number.str() << ", " << value.str();
    std::string line = ss.str();

    return line;
}

vector<data_format> csv_in(string file)
{
    std::ifstream csv_in(file);
    vector<data_format> csv_data;
    string line;
    while(getline(csv_in, line)) {
        data_format data = deserialize(line);
        csv_data.push_back(data);
    }
    return csv_data;
}

void csv_out(const vector<data_format>& data, string file)
{
    std::ofstream csv_out(file);
    for (auto d : data) {
        string s = serialize(d);
        cout << s << endl;
        //csv_out << s << std::endl;
    }
}

void dummy(string& s, int& i, double& d)
{
    std::cout << s << ", " << i << ", " << d << std::endl;
    s += ".sup";
    i += 42;
    d *= 2.0;
}

void test_csv()
{
    vector<data_format> data_in = csv_in("testin.csv");
    vector<data_format> data_out;
    for (auto d : data_in) {
        dummy(d.name, d.number, d.value);
        data_out.push_back(d); // modified by dummy() function
    }
    csv_out(data_out, "testout.csv");
}

int main()
{
    test_csv();
    return 0;
}

