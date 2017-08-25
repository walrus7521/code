#include <iostream>

// add peek n with buffer passed in
// could be better in c++?

template <typename T>
class fifo
{
public:
    fifo(int sz): 
        size_(sz), buffer_(new T[size_]), read_(0), write_(0), data_(0)
    { std::cout << "ctor\n"; }
    ~fifo() { std::cout << "dtor\n"; delete [] buffer_; } 
    bool full() { return (data_ == size_); }
    bool empty() { return (data_ == 0); }
    void put(T e) {if (!full()) { buffer_[write_] = e; write_ = (write_+1)%size_; data_++;}}
    void put2(T e) { buffer_[write_] = e; write_ = (write_+1)%size_; data_++; if (data_ >= size_) data_ = size_; }
    T get() { T e = buffer_[read_]; read_ = (read_+1)%size_; --data_; return e; }
    T peek() { return buffer_[read_]; }
    int size() { return size_; }
    int space() { return (size_-data_); }

private:
    int read_;
    int write_;
    int size_;
    int data_;
    T *buffer_;
};

int main()
{
    fifo<char> f(8);
    for (int i = 0; i < 26; ++i) {
        f.put2((char) ('a'+i));
    }
    while (!f.empty()) {
        char cc = f.peek();
        char c = f.get();
        int n = f.space();
        std::cout << "space: " << n << ", peek: " << cc << ", got: " << c << std::endl;
    }
}

