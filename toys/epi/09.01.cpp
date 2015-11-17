#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <stack>

using std::cout;
using std::endl;
using std::pair;
using std::stack;
using std::length_error;

class Stack {
public:
    bool Empty() const { return element_with_cached_max_.empty(); }

    int Max() const {
        if (!Empty()) {
            return element_with_cached_max_.top().second;
        }
        throw length_error("Max(): empty stack");
    }

    int Pop() {
        if (Empty()) {
            throw length_error("Pop(): empty stack");
        }
        int pop_element = element_with_cached_max_.top().first;
        element_with_cached_max_.pop();
        return pop_element;
    }

    void Push(int x) {
        element_with_cached_max_.emplace(
                x, std::max(x, Empty() ? x : element_with_cached_max_.top().second));
    }

private:
    stack<pair<int, int>> element_with_cached_max_;
};

int main()
{
    Stack s;

    s.Push(11);
    s.Push(2);
    s.Push(333);
    s.Push(4);
    s.Push(55);
    s.Push(6);
    s.Push(7);
    s.Push(88);

    cout << "max = " << s.Max() << endl;
    cout << "pop = " << s.Pop() << endl;
    cout << "pop = " << s.Pop() << endl;
    cout << "pop = " << s.Pop() << endl;

    return 0;
}
