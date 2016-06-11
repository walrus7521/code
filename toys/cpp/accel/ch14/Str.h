#include <iostream>
#include <cstring>
#include "Ptr.h"
#include "Vec.h"

class Str {
    friend std::istream& operator>>(std::istream&, Str&);

public:
    typedef Vec<char>::size_type size_type;

    Str() { std::cout << "invoking Str()..\n"; }

    Str(size_type n, char c): data(n, c) {
        std::cout << "invoking Str(n, c)..\n";
    }

    Str(const char *cp) {
        std::cout << "invoking Str(cp)..\n";
        std::copy(cp, cp+std::strlen(cp), std::back_inserter(data));
    }

    template <class In> Str(In b, In e) {
        std::cout << "invoking Str(b, e)..\n";
        std::copy(b, e, std::back_inserter(data));
    }

    char& operator[](size_type i) { return data[i]; }
    const char& operator[](size_type i) const { return data[i]; }
    Str& operator+=(const Str& s) {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }
    size_type size() const {return data.size(); }

private:
    Vec<char> data;
};

std::istream& operator>>(std::istream& is, Str& s)
{
    s.data.clear();

    char c;
    while (is.get(c) && isspace(c))
        ;
    if (is) {
        do s.data.push_back(c);
        while (is.get(c) && !isspace(c));

        if (is)
            is.unget();
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Str& s)
{
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}

Str operator+(const Str& s, const Str& t)
{
    Str r = s;
    r += t;
    return r;
}


