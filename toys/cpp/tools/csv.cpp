#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

// alter this to match the csv format
struct data_format {
    string name;
    int number;
    double value;
};

// get rid of comma
data_format formatter(string line)
{
    std::stringstream ss(line); // create a stream of string
    string name, number, value;
    data_format data;
    ss >> name >> number >> value;
    data.name   = name;
    data.number = atoi(number.c_str());
    data.value  = atof(value.c_str());
    return data;
}

vector<data_format> csv_in(string file)
{
    std::ifstream in(file);
    vector<data_format> csv_data;
    string line;
    while(getline(in, line)) {
        data_format data = formatter(line);
        csv_data.push_back(data);
    }
    return csv_data;
}

vector<data_format> csv_in2()
{
    std::ifstream readFile("testin.csv");
    vector<string> csv_line;
    vector<data_format> csv_data;
    string line;

    while(getline(readFile,line))   {
        std::stringstream ss(line); // create a stream of string
        csv_line.clear(); // clear out the csv line
        std::string item; // individual items in the line
        while(std::getline(ss, item, ',')) // split string into items
        {
            csv_line.push_back(item);
            cout << item << endl;
        }
        data_format data;
        data.name   = csv_line[0];
        data.number = atoi(csv_line[1].c_str());
        data.value  = atof(csv_line[2].c_str());
        csv_data.push_back(data);
    }
    return csv_data;
}

void csv_out(const vector<string>& vs)
{
    std::ofstream writeFile("testout.csv");
    for (auto s : vs) {
        writeFile << s << std::endl;
    }
}

void dummy(string& s, int& i, double& d)
{
    s += ".sup";
    i += 42;
    d *= 2.0;
}

void test_csv()
{
    vector<data_format> vs = csv_in("testin.csv");
    for (auto s : vs) {
        std::cout << s.name << std::endl;
        std::cout << s.number << std::endl;
        std::cout << s.value << std::endl;
    }
#if 0
    string s = vs[0];
    int    i = atoi(vs[1].c_str());
    char* pEnd;
    double d = atof(vs[2].c_str());
    std::cout << "str: " << s << ", i: " << i << ", d: " << d << std::endl;
    dummy(s, i, d);
    std::cout << "str: " << s << ", i: " << i << ", d: " << d << std::endl;

    std::ostringstream stringStream;
    stringStream << s << ", " << i << ", " << d;
    std::string copyOfStr = stringStream.str();

    vector<string> vs_out;
    vs_out.push_back(copyOfStr);
    csv_out(vs_out);
#endif
}

int main()
{
    test_csv();
    return 0;
}

