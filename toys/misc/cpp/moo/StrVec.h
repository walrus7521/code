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
    StrVec(StrVec &&s) noexcept; // move constructor, won't throw
    StrVec &operator=(StrVec&&) noexcept; // move assign, won't throw
    ~StrVec();                        // destructor
    template <class... Args> void emplace_back(Args&&...);
    void push_back(const std::string&); // copy the element
    void push_back(std::string&&); // move the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...

private:
    static std::allocator<std::string> alloc; // allocates the elements
    void chk_n_alloc() { // used by functions that add elements to a StrVec
        if (size() == capacity()) {
            //reallocate_copy();
            reallocate_move();
        }
    }
    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string*, std::string*> alloc_n_copy(
            const std::string*, const std::string*);
    void free();
    void reallocate_copy();
    void reallocate_move();

    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

// alloc must be defined in the StrVec implementation file
std::allocator<std::string> StrVec::alloc;

using namespace std;

void StrVec::push_back(const string& s)
{
    std::cout << "push_back copy" << std::endl;
    chk_n_alloc(); // ensure that there is rooom for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

void StrVec::push_back(string&& s)
{
    std::cout << "push_back move" << std::endl;
    chk_n_alloc(); // ensure that there is rooom for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, std::move(s));
}

template <typename T>
void work(const T &t)
{
    std::cout << "special work: " << t << std::endl;
}
template <typename T, class... Args>
void work(const T &t, Args&&... args)
{
    std::cout << "work: " << t << std::endl;
    work(args...);
}

template <class... Args>
inline
void StrVec::emplace_back(Args&&... args)
{
    //chk_n_alloc(); // reallocates StrVec if necessary
    //alloc.construct(first_free++, std::forward<Args>(args)...);
    work(std::forward<Args>(args)...);
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

// move constructor
StrVec::StrVec(StrVec &&s) noexcept // move won't throw, tells compiler it is safe
    // member initializers take over the resources in s
    // all are pointers
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    std::cout << "move ctor" << std::endl;
    // leave s in a state in which it is safe to run the destructor
    // ie, doing so won't mess up the resource in the moved to class
    // since these are pointers.
    s.elements = s.first_free = s.cap = nullptr;
}

// move assignment
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    std::cout << "move assn" << std::endl;
    // guard agains self assignment
    if (this != &rhs) {
        free(); // free existing elements
        elements = rhs.elements; // take over resources from rhs
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
 
void StrVec::reallocate_copy()
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
        // construct (copy) corresponding element in the new space
        alloc.construct(dest++, std::move(*elem++));
    }
    free(); // free the old space once we've moved the elements
    // update our data structure to point to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reallocate_move()
{
    // allocate space for 2x as many elements as current size
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);

    // move the elements
    // uninitialized_copy calls construct on each element
    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()),
                                   first);

    free(); // free the old space once we've moved the elements
    // update our data structure to point to the new elements
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}


#endif // STR_VEC_H
