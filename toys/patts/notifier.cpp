#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename Listener>
class Notifier
{
public:
    void AddListener(Listener* listener) {
        assert(find(mListeners.begin(), mListeners.end(), listener) ==
                mListeners.end()); // should be false, no duplicates
        mListeners.emplace_back(listener);
    }
    void RemoveListener(Listener* listener) {
        auto object = find(mListeners.begin(), mListeners.end(), listener);
        if (object != mListeners.end()) {
            mListeners.erase(object);
        }
    }
    // method pointers (function pointers)
    template <void (Listener::*Method)()>
    void Notify() {
        for (auto& listener : mListeners) {
            (listener->*Method)();
        }
    }
private:
    using Listeners = std::vector<Listener*>;
    Listeners mListeners;
};

class AbstractListener
{
public:
    virtual void Handler() = 0;
};

class ConcreteListener : public AbstractListener
{
private:
    int _id;
public:
    ConcreteListener(int id) : _id(id) {}
    void Handler(){ cout << "notifying: listener" << _id << endl; }
};

class Event : public Notifier<AbstractListener>
{
public:
    void Trigger() {
        Notify<&AbstractListener::Handler>();
    }
};

int main()
{
    Event e;
    ConcreteListener ob1(1);
    ConcreteListener ob2(2);
    ConcreteListener ob3(3);

    e.AddListener(&ob1);
    e.AddListener(&ob2);
    e.AddListener(&ob3);

    e.Trigger();
}
