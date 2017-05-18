#include <iostream>
#include <sstream>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;

bool binary_mode = false;
bool enabled  = true;
std::mutex sniff_mutex;
std::atomic<bool> sniff;
std::vector<char> sniffed_data;

extern void set_binary(bool bin);
//{
//    std::lock_guard<std::mutex> lock(sniff_mutex);
//    binary_mode = bin;
//}

void enable_sniff(bool enable)
{
    std::lock_guard<std::mutex> lock(sniff_mutex);
    if (enable != sniff) {
        sniff = enable;
        sniffed_data.clear();
    }
}

void write(const char * data, uint32_t size)
{
    if (enabled) {
        if (sniff) {
            // Lock to prevent multiple threads from reading data simultaneously, which
            // would potentially cause data access errors.
            std::lock_guard<std::mutex> lock(sniff_mutex);
            sniffed_data.insert(sniffed_data.end(), data, data + size);
        }
    }
}

void get_data(std::vector<char> & data)
{
    std::lock_guard<std::mutex> lock(sniff_mutex);
    data.insert(data.end(), sniffed_data.begin(), sniffed_data.end());
}

void show_data()
{
    std::lock_guard<std::mutex> lock(sniff_mutex);
    for (auto s : sniffed_data) {
        cout << s << endl;
    }
}

int main()
{
    set_binary(true);
    enable_sniff(true);
    write("this ", 5);
    write("is ", 3);
    write("the day", 7);
    show_data();
}
