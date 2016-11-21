#ifndef STR_VEC_H
#define STR_VEC_H

#include <string>
#include <memory>
#include <utility>


// 1. obtain new space
// 2. move existing elements to new space
// 3. free old space
// 4. add new element

class StrVec {
public:
    StrVec() :
        elements(nullptr), first_free(nullptr), cap(nullptr) {
            std::cout << "ctor" << std::endl;
        }
    StrVec(const StrVec&);            // copy constructor
    StrVec &operator=(const StrVec&); // copy assign
    ~StrVec();                        // destructor
    void push_back(const std::string&); // copy the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...

private:
    static std::allocator<std::string> alloc; // allocates the elements
    void chk_n_alloc() { // used by functions that add elements to a StrVec
        if (size() == capacity()) {
            reallocate();
        }
    }
    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string*, std::string*> alloc_n_copy(
            const std::string*, const std::string*);
    void free();
    void reallocate();

    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

// alloc must be defined in the StrVec implementation file
std::allocator<std::string> StrVec::alloc;

using namespace std;

void StrVec::push_back(const string& s)
{
    chk_n_alloc(); // ensure that there is rooom for another element
    // construcgt a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    // may not pass deallocate a 0 pointer; if element is 0, there's no work to do
    if (elements) {
        // destroy the old elements in reverse order
        for (auto p = first_free; p != elements; /* empty */) {
            alloc.destroy(--p); // runs the string destructor
        }
        alloc.deallocate(elements, cap - elements); // frees the memory
    }
}

// copy constructor
StrVec::StrVec(const StrVec &s)
{
    std::cout << "copy con" << std::endl;
    // call alloc_n_copy to allocate exactly as many elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first; // of the pair == begin()
    first_free = cap = newdata.second; // of the pair == end()
}

StrVec::~StrVec() { 
    std::cout << "dtor" << std::endl;
    free(); 
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    std::cout << "copy assn" << std::endl;
    // call copy_n_alloc first to allocate exactly as many elements in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free(); // free elements before assigning the new pointer
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    // allocate space for 2x as many elements as current size
    auto newcapacity = size() ? 2 * size() : 1;
    // allocate new memory
    auto newdata = alloc.allocate(newcapacity);
    // move the data fro the old memory to the new
    auto dest = newdata; // points to the next free position in the new array
    auto elem = elements; // points to the next element in the old array
    // iterate through the existing elements
    for (size_t i = 0; i != size(); ++i) {
        // construct corresponding element in the new space
        alloc.construct(dest++, std::move(*elem++));
    }
    free(); // free the old space once we've moved the elements
    // update our data structure to point to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}


#endif // STR_VEC_H
