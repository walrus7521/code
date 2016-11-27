#ifndef STR_BLOB_H
#define STR_BLOB_H

#include <vector>
#include <string>
#include <memory>

using namespace std;

template <typename T>
class Blob {
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;

    Blob() : data(make_shared<vector<T>>()) {}
    Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    void push_back(const T &t) { 
        data->push_back(t); 
    }
    void pop_back() {
        check(0, "pop_back on empty Blob");
        return data->pop_back();
    }
    // element access
    T& front() {
        check(0, "front on empty Blob");
        return data->front();
    }
    T& back() {
        check(0, "back on empty Blob");
        return data->back();
    }
    T& front() const {
        check(0, "front on empty Blob");
        return data->front();
    }
    T& back() const {
        check(0, "back on empty Blob");
        return data->back();
    }
    T& operator[](size_type i) {
        check(i, "subscript out of range");
        return (*data)[i];
    }

private:
    shared_ptr<vector<T>> data;
    // throws msg if data isn't valid
    void check(size_type i, const string &msg) const {
        if (i >= data->size()) {
            throw out_of_range(msg);
        }
    }

};

#endif // STR_BLOB_H
