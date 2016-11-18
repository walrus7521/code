#ifndef STRBLOB_H
#define STRBLOB_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob(): data(std::make_shared<std::vector<std::string>>()){}
    StrBlob(std::initializer_list<std::string> il):
        data(std::make_shared<std::vector<std::string>>(il)){}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string& front();
    std::string& back();
    StrBlobPtr begin();
    StrBlobPtr end();
//private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr {
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0):
        wptr(a.data), curr(sz) {}
    std::string& deref() const;
    StrBlobPtr& incr();
private:
        std::shared_ptr<std::vector<std::string>>
            check(std::size_t, const std::string&) const;
        std::weak_ptr<std::vector<std::string>> wptr;
        std::size_t curr;
};

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size()) 
        throw std::out_of_range(msg);
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

#endif
