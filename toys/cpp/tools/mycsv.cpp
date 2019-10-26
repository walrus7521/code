#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <type_traits>

using namespace std;

struct schema {
    string name;
    int id;
    float age;
};

schema the_row;
ifstream fin;

void parse_row(vector<string>& row)
{
    the_row.name = string(row[0]);
    the_row.id   = stoi(row[1]);
    the_row.age  = stof(row[2]);
}

void csv_init(char *filename)
{
    fin.open(string(filename), ios::in); 
}

int get_next_row()
{
    vector<string> row; 
    string line, word; 
    if (fin.good()) {
        row.clear(); 
        getline(fin, line); 
        istringstream s(line); 
        while (std::getline(s, word, ',')) { 
            row.push_back(word); 
        } 
        parse_row(row);
        return 1;
    }
    return 0;
}

void dump_row()
{
    printf("%s, %d, %f\n", the_row.name.c_str(), the_row.id, the_row.age);
}

int main()
{
    char filename[] = "testin.csv";
    csv_init(filename);
    while(get_next_row()) {
        dump_row();
    }
}

