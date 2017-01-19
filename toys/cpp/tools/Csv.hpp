#ifndef _CSV_H_
#define _CSV_H_


// alter this to match the csv format
struct data_format {
    std::string name;
    int number;
    double value;
};


template <typename T>
T deserialize(std::string line)
{
    std::stringstream ss(line); // create a stream of string
    std::string item; // generic string to retrieve individual items
    T data; // format structure, see above
    // need to use getline to eliminate the comma
    std::getline(ss, item, ','); data.name   = item;
    std::getline(ss, item, ','); data.number = atoi(item.c_str());
    std::getline(ss, item, ','); data.value  = atof(item.c_str());
    return data;
}

template <typename T>
std::string serialize(T data)
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

template <typename T>
std::vector<float> csv_in(std::string file, std::vector<int> columns)
{
    std::ifstream csv_in(file);
    std::vector<T> csv_data;
    std::string line;
    while(getline(csv_in, line)) {
        T data = deserialize<T>(line);
        csv_data.push_back(data);
    }
    return csv_data;
}

template <typename T>
void csv_out(const std::vector<T>& data, std::string file)
{
    std::ofstream csv_out(file);
    for (auto d : data) {
        std::string s = serialize<T>(d);
        csv_out << s << std::endl;
    }
}

#endif // _CSV_H_

