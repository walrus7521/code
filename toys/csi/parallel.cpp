#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

using namespace std;

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id, string s) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready) cv.wait(lck);
  // ...
  std::cout << "thread: " << s << " id: " << id << '\n';
}

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i) threads[i] = std::thread(print_id,i,"dude");

  std::cout << "10 threads ready to race...\n";
  for (int i = 0; i < 4; ++i) {
      std::cout << "dude    . \r";// << endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  go();                       // go!

  for (auto& th : threads) th.join();

  return 0;
}

