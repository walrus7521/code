#include <iostream>
#include <vector>
#include <exception>

template <typename T>
struct link_t {
    link_t(const T& data) : data(data), next(0) {}
    T data;
    std::shared_ptr<link_t<T>> next;
};

// generic show: lists and arrays
// create an iterator abstraction
template <typename T>
struct list_iterator {
    using value_type = T;

    list_iterator(std::shared_ptr<link_t<T>> entry) : entry(entry) {}

    T& operator*() { return entry->data; }
    const T& operator*() const { return entry->data; }

    list_iterator<T> operator++() {
        entry = entry->next; return *this;
    }
    list_iterator<T> operator++(int i) {
        list_iterator<T> tmp(*this);
        entry = entry->next; 
        return tmp;
    }

    bool operator!=(const list_iterator<T>& other) const
    { return entry != other.entry; }

    std::shared_ptr<link_t<T>> entry;
};

template <typename T>
struct list {
    list() : first(0), last(nullptr) {}
    ~list() {
        while (first) {
            auto tmp = first->next;
            first = tmp;
        }
    }
    void append(const T& x) {
        auto tmp = std::make_shared<link_t<T>>(x);
        last = (first? last->next : first) = tmp; //std::make_shared<link_t<T>>(x);
    }

    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }

    std::shared_ptr<link_t<T>> first, last;
};

template <typename T>
void show(const T& l)
{
    std::cout << "using non-generic" << std::endl;
    for (auto entry = l.first; entry != nullptr; entry = entry->next) {
        std::cout << entry->data << std::endl;
    }
}

template <typename Iter, typename T>
void show(Iter it, Iter end, T init)
{
    std::cout << "using generic" << std::endl;
    for (; it != end; ++it) {
        std::cout << *it << std::endl;
    }
}

template <typename Vector1, typename Vector2>
auto operator+(const Vector1& v1, const Vector2& v2)
//    -> std::vector< decltype(v1[0] + v2[0]) >
{
    return (v1[0] + v2[0]);
}

void stuff()
{
    auto i = 3;
    std::cout << i << std::endl;

    std::vector<int> v3 = {1,2,3};
    std::vector<int> v4 = {4,5,6};

    int i3;
    decltype(auto) x = (i3 = v3 + v4);
    std::cout << x << std::endl;
}

template <typename Vector>
class value_range_vector
{
    using value_type = typename Vector::value_type;
    using size_type  = typename Vector::size_type;
public:
    value_range_vector(Vector& vref, value_type minv, value_type maxv)
        : vref(vref), minv(minv), maxv(maxv)
    {}

    decltype(auto) operator[](size_type i)
    {
        decltype(auto) value = vref[i];
        if (value < minv) throw std::range_error("dude"); //too_small();
        if (value > maxv) throw std::range_error("sup"); //too_large();
        return value;
    }
private:
    Vector& vref;
    value_type minv, maxv;
};

template <unsigned Order, typename Value>
class tensor {};

template <typename Value>
using vector = tensor<1, Value>;

template <typename Value>
using matrix = tensor<2, Value>;

void stuff2()
{
    using Vec = std::vector<double>;
    Vec v = {2.3, 8.1, 9.2};

    value_range_vector<Vec> w(v, 1.0, 10.0);
    decltype(auto) val = w[1];
    std::cout << val << std::endl;

    std::cout << "type of vector<float> is " 
        << typeid(vector<float>).name() << '\n';
    std::cout << "type of matrix<float> is "
        << typeid(matrix<float>).name() << '\n';

}

template <typename T>
class rector
{
public:
    explicit rector(int size)
        : my_size(size), data(new T[my_size])
    {}
    rector(const rector& that)
        : my_size(that.my_size), data(new T[my_size])
    {
        std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
    }
    int size() const { return my_size; }
    const T& operator[](int i) const
    {
        return data[i];
    }
private:
    int my_size;
    std::unique_ptr<T[]> data;
};


template <>
class rector<bool>
{
};

int main()
{
    stuff();
    stuff2();
    return 0;

    list<int> l;
    l.append(1);
    l.append(2);
    l.append(3);
    show(l);
    show(l.begin(), l.end(), 0);

    int a[] = {2,4,7};
    double d[] = {3.14,1.15,2.17};

    show(a, a+3, 0);
    show(d, d+3, 0.0);

}

