#include <iostream>

template <typename T>
class fifo {
    public:
        fifo(int s): sz{s}, elem{new T[s]} {
            std::cout << "ctor" << std::endl;
            n = rd = wr = 0;
        }
        ~fifo() { std::cout << "dtor" << std::endl; delete[] elem; }
        T& operator[](int i) { return elem[i]; }
        int enqueue(T v) { elem[wr++] = v; n++; return 0; }
        T dequeue() { T e = elem[rd++]; n--; return e; }
        int size() { return sz; }
        int count() { return n; }
    private:
        int sz;
        int n; // num elements in fifo
        int rd;
        int wr;
        T* elem;
};

int main()
{
    fifo<int> f(32);
    f.enqueue(42);
    f.enqueue(84);
    f[2] = 17;
    std::cout << f[0] << std::endl;
    std::cout << f[1] << std::endl;
    std::cout << f[2] << std::endl;
    std::cout << f.dequeue() << std::endl;
    std::cout << f.dequeue() << std::endl;
    std::cout << f.dequeue() << std::endl;
    return 0;
}
