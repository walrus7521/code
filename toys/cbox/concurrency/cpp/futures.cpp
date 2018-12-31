#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <iostream>

using namespace std;

string loader()
{
    string loader_loaded {"bart"};
    cout << "wudup\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    return loader_loaded;
}

void run()
{
    packaged_task<string()> loader_task{ loader };

    future<string> f{loader_task.get_future()};

    thread loader_thread{ move(loader_task) };

    while (f.wait_for(std::chrono::milliseconds{500})
            != std::future_status::ready) {
        // waiting
        cout << "waiting\n";
    }
    loader_thread.join();

    string loaded = f.get();

    cout << "dude: " << loaded << endl;

}

int main()
{
    try {
        run();
        cout << "hooda\n";
    } catch (...) {
        cout << "exception\n";
    }
    return 0;
}
