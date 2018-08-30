#include <iostream>
#include <exception>
#include <stdexcept>

// thread safe, factory, noexcept

template <typename T>
class fifo {
    public:
        fifo(int s): sz{s}, elem{new T[s]} {
            std::cout << "ctor" << std::endl;
            n = rd = wr = 0;
        }
        ~fifo() { std::cout << "dtor" << std::endl; delete[] elem; }
        T& operator[](int i) { 
            if (i < 0) {
                throw std::length_error{"fifo [] bad index"};
            }
            if (i >= sz) {
                throw std::out_of_range{"fifo [] out of range"};
            }
            return elem[i]; 
        }
        int enqueue(T v) noexcept { elem[wr++] = v; n++; return 0; }
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
    constexpr int size = 16;
    static_assert(size <= 16, "fifo size too large");
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
    try {
        std::cout << f[-7] << std::endl;
        std::cout << f[32] << std::endl;
    } catch (std::out_of_range) {
        std::cout << "caught out of range access" << std::endl;
    } catch (std::length_error) {
        std::cout << "caught length error" << std::endl;
    }
    return 0;
}

