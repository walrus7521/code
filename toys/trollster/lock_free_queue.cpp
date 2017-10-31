#include <atomic>
#include <thread>
#include <iostream>

// http://www.drdobbs.com/parallel/writing-a-generalized-concurrent-queue/211601363?pgno=4

using namespace std;

#define CACHE_LINE_SIZE 8

template <typename T>
struct LowLockQueue {
private:
    struct Node {
        Node( T* val ) : value(val), next(nullptr) { }
        T* value;
        atomic<Node*> next;
        //char pad[CACHE_LINE_SIZE - sizeof(T*)- sizeof(atomic<Node*>)];
    };
    //char pad0[CACHE_LINE_SIZE];
 
    // for one consumer at a time
    Node* first;
    //char pad1[CACHE_LINE_SIZE - sizeof(Node*)];
 
    // shared among consumers
    atomic<bool> consumerLock;
    //char pad2[CACHE_LINE_SIZE - sizeof(atomic<bool>)];

    // for one producer at a time
    Node* last; 
    //char pad3[CACHE_LINE_SIZE - sizeof(Node*)];
 
    // shared among producers
    atomic<bool> producerLock;
    //char pad4[CACHE_LINE_SIZE - sizeof(atomic<bool>)];

public:
    LowLockQueue() {
        first = last = new Node( nullptr );
        producerLock = consumerLock = false;
    }

    ~LowLockQueue() {
        while( first != nullptr ) {  // release the list
            Node* tmp = first;
            first = tmp->next;
            delete tmp->value;       // no-op if null
            delete tmp;
        }
    }

    void Produce( const T& t, int id ) {
        Node* tmp = new Node( new T(t) );
        while( producerLock.exchange(true) ) {} // acquire exclusivity
        last->next = tmp;       // publish to consumers
        last = tmp;             // swing last forward
        producerLock = false;   // release exclusivity
        std::cout << "pro id: " << id << '\n';
    }

    bool Consume( T& result, int id ) {
        while( consumerLock.exchange(true) ) {} // acquire exclusivity
        Node* theFirst = first;
        Node* theNext = first-> next;
        if ( theNext != nullptr ) {   // if queue is nonempty
            T* val = theNext->value;  // take it out
            theNext->value = nullptr; // of the Node
            first = theNext;          // swing first forward
            consumerLock = false;     // release exclusivity
            result = *val;    // now copy it back
            delete val;       // clean up the value
            delete theFirst;  // and the old dummy
            std::cout << "con id: " << id << '\n';
            return true;      // and report success
        }
        consumerLock = false;   // release exclusivity
        return false;           // report queue was empty
    }

};

LowLockQueue<int> llq;

void produce(int id)
{
    int i = 0;
    while (true) {
        llq.Produce(i, id);
        i++;
    }
}

void consume(int id)
{
    int i;
    while (true) {
        if (llq.Consume(i, id)) {
            //std::cout << "cons: " << i << std::endl;
        }
    }
}

int main()
{

    std::thread t1 = std::thread(produce, 1);
    std::thread t2 = std::thread(consume, 2);
    std::thread t3 = std::thread(produce, 3);
    std::thread t4 = std::thread(consume, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

}
