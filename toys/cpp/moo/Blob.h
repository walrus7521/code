#ifndef STR_BLOB_H
#define STR_BLOB_H

#include <vector>
#include <string>
#include <memory>
#include <utility>

using namespace std;

template <typename T>
class Blob {

public:
    friend ostream& operator<<(ostream &os, Blob<T> &blob) {
        return os << (*blob.data)[blob.curr];
    }

    typedef T value_type;
    typedef typename vector<T>::size_type size_type;

    Blob() : data(make_shared<vector<T>>()), curr(0) {}
    Blob(initializer_list<T> il) : 
        data(make_shared<vector<T>>(il)), curr(0) 
    {}

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
    Blob& operator++() {
        ++curr;
        return *this;
    }
    Blob& operator--() {
        --curr;
        return *this;
    }
    Blob& operator++(int) {
        Blob &ret = *this;
        ++curr;
        return ret;
    }
    Blob& operator--(int) {
        Blob &ret = *this;
        --curr;
        return ret;
    }
    auto begin() {
        return data->begin();
    }
    auto end() {
        return data->end();
    }

private:
    shared_ptr<vector<T>> data;
    size_t curr;
    // throws msg if data isn't valid
    void check(size_type i, const string &msg) const {
        if (i >= data->size()) {
            throw out_of_range(msg);
        }
    }

};

typedef Blob<string> StrBlob;
typedef Blob<int> IntBlob;

// clump is a synonym for Blob<T>
template<typename T> using clump = Blob<T>;

template <typename T> using twin = pair<T,T>;
template <typename T> using partNo = pair<T, unsigned>;

//template <typename T>
//ostream& operator<<(ostream &os, Blob<T> &blob) {
//    return os << (*blob.data)[blob.curr];
//}


#endif // STR_BLOB_H
