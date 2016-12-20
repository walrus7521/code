#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>

template <typename T>
class Stack {
private:
    std::vector<T> elems;

public:
    void push(T const& elem) {
        std::cout << "generic" << std::endl;
        elems.push_back(elem);
    }
    T pop() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::pop empty stack");
        }
        T elem = elems.back();
        elems.pop_back();
        return elem;
    }
    T top() const {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::top empty stack");
        }
        return elems.back();
    }
    bool empty() const {
        return elems.empty();
    }
    size_t size() const {
        return elems.size();
    }
};

// specialization of stack to strings
template <>
class Stack<std::string> {
private:
    std::deque<std::string> elems;

public:
    void push(std::string const& elem) {
        std::cout << "specialized" << std::endl;
        elems.push_back(elem);
    }
    std::string pop() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::pop empty stack");
        }
        std::string elem = elems.back();
        elems.pop_back();
        return elem;
    }
    std::string top() const {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::top empty stack");
        }
        return elems.back();
    }
    bool empty() const {
        return elems.empty();
    }
    size_t size() const {
        return elems.size();
    }
};


using namespace std;

typedef Stack<int> IntStack;
void foo(IntStack const& s)
{
    Stack<int> is[10];
    for (int i = 22; i < 32; ++i) {
        for (int j = 0; j < s.size(); ++j) {
            is[i].push(j);
        }
    }
}

int main()
{
    try {
        Stack<int> si;
        Stack<string> ss;
        si.push(42);
        cout << "pop i  : " << si.pop() << endl;
        ss.push("poser");
        cout << "pop str: " << ss.pop() << endl;

        IntStack is;
        foo(is);

    } catch (std::exception const& ex) {
        cerr << "Exception: " << ex.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
