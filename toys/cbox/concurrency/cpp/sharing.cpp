#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

using namespace std;

mutex m1;
mutex m2;
mutex m3;
int sh;

void f(vector<double>& v, double *res) {
    unique_lock<mutex> lck1 {m1, defer_lock};
    unique_lock<mutex> lck2 {m2, defer_lock};
    unique_lock<mutex> lck3 {m3, defer_lock};
    lock(lck1, lck2, lck3);
    cout << "Hello\n";
    sh++;
    *res = 42;
}

class F {
public:
    F(vector<double>& vv, double *p) : v{vv}, res{p} {}
    void operator()() { 
        unique_lock<mutex> lck1 {m1, defer_lock};
        unique_lock<mutex> lck2 {m2, defer_lock};
        unique_lock<mutex> lck3 {m3, defer_lock};
        lock(lck1, lck2, lck3);
        cout << "Parallel World!\n"; *res = 17; 
        sh--;
    };
private:
    const vector<double>& v;
    double *res;
};

void user()
{
    vector<double> some_vec {1,2,3,4,5,6,7,8,9};
    vector<double> vec2 {10,11,12,13,14};

    double res1;
    double res2;

    sh = 42;

    thread t1 {f, ref(some_vec), &res1};
    thread t2 {F(vec2, &res2)};

    t1.join(); // wait for thread to terminate
    t2.join();

    cout << res1 << '-' << res2 << '-' << sh << '\n';
}

int main()
{
    user();
    return 0;
}
