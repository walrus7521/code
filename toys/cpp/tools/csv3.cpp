// csv.hpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using vec_str = std::vector<std::string>;

class CSV_MINI {
public:
    CSV_MINI(){}
    void open(std::string& name)
    {
        m_file.open(name);
    }
    std::vector<vec_str> reader(char delim)
    {
        std::string line;
        while (getline(m_file, line)) {
            vec_str data = split(line, delim);
            m_csv_data.push_back(data);
        }
        return m_csv_data;
    }
    std::vector<std::string> get_col(int col)
    {
        std::vector<std::string> vs;
        int n_rows = m_csv_data.size();
        vs.resize(n_rows);
        std::cout << "n rows: " << n_rows << '\n';
        for (int i = 0; i < n_rows; ++i) { //auto &row : csv_rows) {
            vs[i] = m_csv_data[i][col];
        }
        return vs;
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
    std::ifstream m_file;
    std::vector<vec_str> m_csv_data;
    char m_delim;
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
    //for (auto &row : csv_rows) {
    //    cout << "frame: " << row[0] << ", raw: " << row[1] << ", cooked: " << row[2] << endl;
    //}

    std::cout << "spew column 1\n";
    std::vector<std::string> col = csv.get_col(1);
    for (auto &row : col) {
        cout << "col 1: " << row << endl;
    }

}


