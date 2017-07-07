#include <iostream>
#include <thread>
#include <chrono>

int state1(int state, int reason)
{
    std::cout << "state1: " << state << " reason: " << reason << std::endl;
}

int state2(int state, int reason)
{
    std::cout << "state1: " << state << " reason: " << reason << std::endl;
}

int state3(int state, int reason)
{
    std::cout << "state1: " << state << " reason: " << reason << std::endl;
}

int state4(int state, int reason)
{
    std::cout << "state1: " << state << " reason: " << reason << std::endl;
}

int callback(int state, int reason)
{
    std::cout << "callback: " << state << " reason: " << reason << std::endl;
}

int monitor(int state, int reason)
{
    std::cout << "monitor: " << state << " reason: " << reason << std::endl;
}

typedef int (*func)(int, int);
func states[4];

int register_event(func f, int context)
{
    f(32, context);
}

void task() {
    std::cout << "task" << std::endl;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        //std::cout << "loopy" << std::endl;
    }
}

struct timer_info {
    int timeout;
    func callback;
} timer_info[16];
int num_timers = 0;
void register_timer(struct timer_info *info)
{
    timer_info[num_timers].timeout = info->timeout;
    timer_info[num_timers].callback = info->callback;
    num_timers++;
}

void timer() {
    static unsigned long long tick = 0;
    std::cout << "timer" << std::endl;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        for (int i = 0; i < num_timers; ++i) {
            if (tick % timer_info[i].timeout == 0) {
                timer_info[i].callback(i, tick);
            }
        }
        ++tick;
    }
}

int main()
{
    int s = 0;
    struct timer_info info;

    states[0] = state1;
    states[1] = state2;
    states[2] = state3;
    states[3] = state4;

    register_event(callback, 63);

    //info.timeout = 4; // frames
    //info.callback = callback;
    //register_timer(&info);

    info.timeout = 50; // frames
    info.callback = callback;
    register_timer(&info);

    info.timeout = 100; // frames
    info.callback = monitor;
    register_timer(&info);

    for (s = 0; s < 4; s++) {
        states[s](s, 77);
    }
    std::thread t1(task);
    std::thread t2(timer);
    t1.join();
    t2.join();

}

