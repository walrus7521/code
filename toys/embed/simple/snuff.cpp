#include <iostream>
#include <sstream>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;

extern std::mutex sniff_mutex;
extern bool binary_mode;

void set_binary(bool bin)
{
    std::lock_guard<std::mutex> lock(sniff_mutex);
    binary_mode = bin;
}


