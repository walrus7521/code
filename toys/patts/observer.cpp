#include <iostream>
#include <vector>
#include <string>

class Observer {
public:
    virtual ~Observer() {}
    virtual void update(int message) = 0;
};

class Subject {
public:
    virtual ~Subject(){};
    virtual void subscribe(Observer *observer) { 
        mObservers.push_back(observer); }
    virtual void unsubscribe (Observer *observer) {
        int count = mObservers.size(); 
        int i; 
        for (i = 0; i < count; i++) { 
            if(mObservers[i] == 0) break; 
        } 
        if (i < count) { 
            mObservers.erase(mObservers.begin() + i);
        }
    }
    virtual void notify(int msg) {
        int count = mObservers.size(); 
        for (int i = 0; i < count; i++) (mObservers[i])->update(msg);
    }
private:
    std::vector<Observer *> mObservers;
};

class ConcreteSubject : public Subject
{
public:
    enum Message {ADD, REMOVE};
};

class ConcreteObserver : public Observer
{
public:
    explicit ConcreteObserver(const std::string &str) : name(str) {}
    void update(int message)
    {
        std::cout << name << " Got message " << message << std::endl;
    }
private:
    std::string name;
};

int main() 
{
    ConcreteObserver observerA("observerA");
    ConcreteObserver observerB("observerB");
    ConcreteObserver observerC("observerC");

    ConcreteSubject subject;
    subject.subscribe(&observerA);
    subject.subscribe(&observerB);
    subject.unsubscribe(&observerB);
    subject.subscribe(&observerC);

    subject.notify(ConcreteSubject::ADD);
    subject.notify(ConcreteSubject::REMOVE);

    return 0;
}
