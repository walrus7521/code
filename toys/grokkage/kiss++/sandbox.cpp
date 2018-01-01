#include <iostream>

// Todo: 
// convert link_t<T>* next; to std::shared_ptr<link_t<T>> next;


template <typename T>
struct link_t {
    link_t(const T& value) : value(value), next(0) {}
    T value;
    link_t<T>* next;
};

// generic show: lists and arrays
// create an iterator abstraction
template <typename T>
struct list_iterator {
    using value_type = T;

    list_iterator(link_t<T>* entry) : entry(entry) {}

    T& operator*() { return entry->value; }
    const T& operator*() const { return entry->value; }

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

    link_t<T> *entry;
};


template <typename T>
struct list {
    list() : first(0), last(nullptr) {}
    ~list() {
        while (first) {
            link_t<T> *tmp = first->next;
            delete first;
            first = tmp;
        }
    }
    void append(const T& x) {
        last = (first? last->next : first) = new link_t<T>(x);
        //last = (first? last->next : first) = make_shared<link_t<T>>(x);
    }

    list_iterator<T> begin() { return list_iterator<T>(first); }
    list_iterator<T> end() { return list_iterator<T>(0); }

    link_t<T> *first, *last;
};

template <typename T>
void show(const T& l)
{
    std::cout << "using non-generic" << std::endl;
    for (auto entry = l.first; entry != nullptr; entry = entry->next) {
        std::cout << entry->value << std::endl;
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

int main()
{
    list<int> l;// = {1,2,3,4};
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

