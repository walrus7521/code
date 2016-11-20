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
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);            // copy constructor
    StrVec &operator=(const StrVec&); // copy assign
    ~StrVec();                        // destructor
    void push_back(const std::string&); // copy the element
    


private:
    void alloc_n_copy();
    void free();
    void chk_n_alloc();
    void reallocate();

    static allocator<string> alloc;
    void *elements;
    void *first_free;
    void *cap;
};

#endif // STR_VEC_H
