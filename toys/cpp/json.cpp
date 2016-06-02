#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
// '{ "name" : "Jack", "age" : 27 }'
//
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::ifstream;


// g++ -std=c++0x json.cpp
//
map<string, vector<string>> map_json2(const vector<string>& json_vs)
{
    map<string, vector<string>> kv_json;
    int line_no = 0;
    string key;
    size_t iIndex;

    // need to get the key value pairs parsed out here
    for (vector<string>::const_iterator it = json_vs.begin();
                it != json_vs.end(); ++it) {
        iIndex = it->rfind(":");
        if(iIndex != std::string::npos && iIndex > 0 && it->length() >= 2)
        {
        //if (iIndex > 0) {
            key = *it;
            continue;
        }
        ////kv_json[*it] = line_no;
        kv_json[key].push_back(*it);
        //cout << "recording " << key << " and " << *it << endl;
        //line_no++;
    }
    return kv_json;

}

// wrong this is an array of maps LOH
map<string, string> map_json(const vector<string>& json_vs)
{
    map<string, string> kv_json;
    int line_no = 0;
    string key;
    size_t iIndex;

    // need to get the key value pairs parsed out here
    for (vector<string>::const_iterator it = json_vs.begin();
                it != json_vs.end(); ++it) {
        iIndex = it->rfind(":");
        if(iIndex != std::string::npos && iIndex > 0 && it->length() >= 2)
        {
        //if (iIndex > 0) {
            key = *it;
            continue;
        }
        ////kv_json[*it] = line_no;
        kv_json[key] = *it;
        //cout << "recording " << key << " and " << *it << endl;
        //line_no++;
    }
    return kv_json;

}

vector<string> des_json(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void dump(const vector<string>& vs)
{
    for (vector<string>::const_iterator it = vs.begin();
                it != vs.end(); ++it) {
        cout << *it << endl;
    }

}

int main()
{

    ifstream infile;
    infile.open("file.json", std::ios::binary);
    infile.seekg(0, std::ios::end);
    size_t file_size_in_byte = infile.tellg();
    std::vector<char> data; // used to store text data
    data.resize(file_size_in_byte);
    infile.seekg(0, std::ios::beg);
    infile.read(&data[0], file_size_in_byte);

    //for (auto c : data) {
    //    cout << c;
    //}
    //cout << endl;

    std::string json_str(data.begin(),data.end());
    cout << json_str << endl;

    vector<string> vs = des_json(json_str);
    //for (auto s : vs) {
    //    std::cout << s << std::endl;
    //}
    //dump(vs);

    map<string, string> msi = map_json(vs);
    for (map<string, string>::const_iterator it = msi.begin();
            it != msi.end(); ++it) {
        cout << "'" << it->first << " : " << it->second;
        cout << endl;
    }
    
    map<string, vector<string>> msii = map_json2(vs);
    for (map<string, vector<string>>::const_iterator it = msii.begin();
            it != msii.end(); ++it) {
        cout << "'" << it->first << endl;
        for (vector<string>::const_iterator vs = it->second.begin();
            vs != it->second.end(); ++vs) {
            cout << *vs << endl;
        }
        cout << endl;
    }


    return 0;
    
}
