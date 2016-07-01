#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>

template <class T> class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    ~Vec<T>() { 
        std::cout << "invoking destructor..\n";
        uncreate(); 
    }
    Vec<T>& operator=(const Vec<T>&);
    Vec(const Vec<T>& v) { 
        std::cout << "invoking copy constructor..\n";
        create(v.begin(), v.end());
    }

    Vec() { create(); }
    explicit Vec(std::size_t n, const T& val = T()) { create(n, val); }

    size_type size() const { return avail - data; }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    void push_back(const T& t) {
        if (avail == limit)
            grow();
        unchecked_append(t);
    }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() {return avail; }
    const_iterator end() const {return avail; }

    void clear() { uncreate(); }
    bool empty() const { return data == avail; }

    
private:
    void uncreate(); // {}
    void create(); // {}
    void create(size_t n, const T& val);
    void create(const_iterator i, const_iterator j);
    void grow();
    void unchecked_append(const T&);

    std::allocator<T> alloc;

    iterator data;    // first element in the Vec
    iterator avail;   // one past the last element in the Vec
    iterator limit;   // one past the last element in the Vec
};

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> void Vec<T>::uncreate()
{
    std::cout << "invoking uncreate(void)..\n";
    if (data) {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = 0;
}

template <class T> void Vec<T>::create()
{
    std::cout << "invoking create(void)..\n";
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_t n, const T& val)
{
    std::cout << "invoking create(size, val)..\n";
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j)
{
    std::cout << "invoking create(i, j)..\n";
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::grow()
{
    std::cout << "invoking grow(void)..\n";
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = new_data + new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    std::cout << "invoking unchecked_append(val)..\n";
    alloc.construct(avail++, val);
}


#endif
