#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue
#include <string>         // std::string, std::getline(string)

class ABPipe
{
public:
    bool SpaceAvailableRead(){ return true; }
    bool SpaceAvailableWrite(){ return true; }
    bool BytesAvailableRead(){ return true; }
    bool BytesAvailableWrite(){ return true; }
private:
    std::queue<char> rdQueue; // from autopilot to Mx app
    std::queue<char> wrQueue; // from Mx app to autopilot
};

int StreamIo
int main ()
{
    std::queue<std::string> myqueue;

    myqueue.emplace ("First sentence");
    myqueue.emplace ("Second sentence");

    std::cout << "myqueue contains:\n";
    while (!myqueue.empty()) {
        std::cout << myqueue.front() << '\n';
        myqueue.pop();
    }

    return 0;
}

