#include <iostream>
#include <queue>

template <typename E> // E is element type
class Queue {
public:
    Queue(){}
    void Enqueue(const E& element) {
        _q.push(element);
    }
    E Dequeue() {
        if (_q.empty()) {
            return -1;
        } else {
            E el = _q.front();
            _q.pop();
            return el;
        }
    }
    size_t size() const { return _q.size(); }
private:
    std::queue<E> _q;
};

#if 0
int main()
{
    Queue<int> q;
    q.Enqueue(42);
    std::cout << q.Dequeue() << std::endl;
}
#endif

