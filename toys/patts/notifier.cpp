#include <iostream>
#include <vector>

template <typename Observer>
class Notifier
{
public:
    void AddObserver(Observer* observer) {
        assert(find(m_observers.begin(), m_observers.end(), observer) ==
                m_observers.end()); // should be false, no duplicates
        m_observers.emplace_back(observer);
    }
    void RemoveObserver(Observer* observer) {
        auto object = find(m_observers.begin(), m_observers.end(), observer);
        if (object != m_observers.end()) {
            m_observers.erase(object);
        }
    }
    // method pointers (function pointers)
    template <void (Observer::*Method)()>
    void Notify() {
        for (auto& observer : m_observers) {
            (observer->*Method)();
        }
    }

private:
    using Observers = std::vector<Observer*>;
    Observers m_observers;
};

int main()
{
}
