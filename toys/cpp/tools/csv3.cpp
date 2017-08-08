It this overly simplistic?  You can access the columns by array index.
// csv.hpp

#include <vector>
#include <string>
#include <fstream>

using vec_str = std::vector<std::string>;

class CSV_MINI {
public:
    CSV_MINI(){}
    void open(std::string& name)
    {
        file.open(name);
    }
    std::vector<vec_str> reader(char delim)
    {
        std::vector<vec_str> csv_data;
        std::string line;
        while (getline(file, line)) {
            vec_str data = split(line, delim);
            csv_data.push_back(data);
        }
        return csv_data;
    }
private:
    bool is_sep_or_white(char a, char sep)
    {
        if (a == sep) return true;
        return isspace(a);
    }
    std::vector<std::string> split(const std::string& s, char sep)
    {
        std::vector<std::string> ret;
        typedef std::string::size_type string_size;
        string_size i = 0;
        while (i != s.size()) {
            // skip white space up to separator
            while (i != s.size() && is_sep_or_white(s[i], sep)) ++i;
            string_size j = i;
            // grab data up to separator
            while (j != s.size() && !is_sep_or_white(s[j], sep)) ++j;
            if (i != j) {
                // the substr is the data
                ret.push_back(s.substr(i, j - i));
                i = j;
            }
        }
        return ret;
    }
    std::ifstream file;
    char delim;
};


// test.cpp

#include "csv.hpp"
#include <iostream>

using namespace std;

string csv_in_filename  = "test5.csv";

int main()
{
    CSV_MINI csv;
    csv.open(csv_in_filename);
    std::vector<vec_str> csv_rows = csv.reader(',');
    for (auto &row : csv_rows) {
        cout << "frame: " << row[0] << ", raw: " << row[1] << ", cooked: " << row[2] << endl;
    }
    
}


