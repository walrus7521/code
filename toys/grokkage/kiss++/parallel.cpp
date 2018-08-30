#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

//using namespace std;

namespace proton {

    std::mutex mtx;
    std::condition_variable notify;
    bool ready = false;

    void print_id (int id, std::string s) {
        std::unique_lock<std::mutex> lck(mtx);
        while (!ready) notify.wait(lck);
        // ...
        std::cout << "thread: " << s << " id: " << id << '\n';
    }

    void go(int num_threads) {
        std::unique_lock<std::mutex> lck(mtx);
        ready = true;
        //notify.notify_all();
        std::cout << "start notify.." << std::endl;
        for (int i = 0; i < num_threads; ++i) {
            std::cout << "notify: " << i << std::endl;
            notify.notify_one();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // need to unlock and relock here
            lck.unlock();
            lck.lock();
        }
    }

} // namespace proton

int main ()
{
    constexpr int nr_threads = 10;
    std::thread threads[nr_threads];
    // spawn 10 threads:
    for (int i=0; i<nr_threads; ++i) threads[i] = std::thread(proton::print_id,i,"dude");

    std::cout << nr_threads << " threads ready to race...\n";
    //for (int i = 0; i < 4; ++i) {
    //    std::cout << "dude    . \r";// << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //}
    proton::go(nr_threads);                       // go!

    for (auto& th : threads) th.join();

    return 0;
}


