#include <cassert>
#include <iostream>
#include <stdexcept> // out_of_range
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <memory>

//constexpr void BUGBUG() { static_assert(false, "fix this code"); }

namespace troll {
    class Vector2
    {
    public:
        Vector2(int size)
            : my_size(size), data(std::make_unique<double[]>(size))
        {
            std::cout << "default ctor\n";
        }
        Vector2(const Vector2& v) // copy constructor
            : my_size(v.my_size), data(std::make_unique<double[]>(v.my_size))
        {
            std::cout << "copy ctor\n";
            for (unsigned i = 0; i < my_size; ++i) {
                data[i] = v.data[i];
            }
        }
        Vector2& operator=(const Vector2& lval) // copy assignment
        {
            std::cout << "copy assn\n";
            if (this == &lval) return *this; // self assn
            assert(my_size == lval.my_size);
            for (unsigned i = 0; i < my_size; ++i) {
                data[i] = lval.data[i];
            }
            return *this;
        }
        // now add initializer copy and assignment constructors
        Vector2(std::initializer_list<double> values)
            : my_size(values.size()), data(std::make_unique<double[]>(values.size()))
        {
            std::cout << "copy ctor intializer\n";
            std::copy(std::begin(values), std::end(values), data.get());
        }
        Vector2& operator=(std::initializer_list<double> values)
        {
            std::cout << "copy assn intializer\n";
            assert(my_size == values.size());
            std::copy(std::begin(values), std::end(values), data.get());
            return *this;
        }
        // move constructor
        Vector2(Vector2&& rval) // rval has a name, so technically its an l-value
            : my_size(rval.my_size), data(std::make_unique<double[]>(rval.my_size))
        {
            std::cout << "move ctor\n";
            //rval.data = nullptr; // is this optional???
            rval.my_size = 0;
        }
        Vector2& operator=(Vector2&& rval)
        {
            std::cout << "move assn\n";
            assert(my_size == 0 || my_size == rval.my_size);
            std::swap(data, rval.data);
            return *this;
        }
        ~Vector2() { std::cout << "dtor\n"; } // no need to set nullptr on unique_ptr
        // operator [] const, and non-const versions
        double& operator[](int i) & { // "&" => only use as l-value
            assert(i >= 0 && i < my_size);
            return data[i];
        }
        const double& operator[](int i) const& { // "&" => only use as l-value
            assert(i >= 0 && i < my_size);
            return data[i];
        }
        double at(int i) {
            assert(i >= 0 && i < my_size);
            return data[i];
        }
        unsigned size() const { return my_size; }
        void const show() {
            if (my_size == 0) {
                std::cout << "empty\n";
                return;
            }
            for (unsigned i = 0; i < my_size; ++i) {
                std::cout << data[i] << ", ";
            }
            std::cout << '\n';
        }
    private:
        std::unique_ptr<double[]> data;
        unsigned my_size;
    };

    enum class Type { Vector, List };

    // abstract type - pure interface
    template <typename T>
    class Container {
    public:
        virtual T& operator[] (int i) = 0;
        virtual int size() const = 0;
        virtual void show() const = 0;

        // delete the copy and move defaults -- broken
        //Container(const Container&) = delete;
        //Container& operator=(const Container&) = delete;
        //Container(const Container&&) = delete;
        //Container operator=(const Container&&) = delete;

        virtual ~Container() {}
    private:
    };

    class Complex {
    public:
        Complex(double r, double i) : re{r}, im{i} {}
        Complex(double r)           : re{r}, im{0} {}
        Complex()                   : re{0}, im{0} {}

        double real() const { return re; }
        void   real(double r) { re = r; }
        double imag() const { return im; }
        void   imag(double i) { im = i; }

        Complex& operator+=(Complex z) { re += z.re, im += z.im; return *this; }
        Complex& operator-=(Complex z) { re -= z.re, im -= z.im; return *this; }
        Complex& operator*=(Complex z) { re *= z.re, im *= z.im; return *this; }
        Complex& operator/=(Complex z) { re /= z.re, im /= z.im; return *this; }

    private:
        double re;
        double im;
    };


    template <typename T>
    class Vector : public Container<T> {
    public:
        Vector() :elem{ nullptr }, sz{ 0 } {}
        explicit Vector(int s) :elem{ new T[s] }, sz{ s } 
        {
            for (int i = 0; i != size(); ++i)  elem[i] = 0;
        }
        Vector(std::initializer_list<T> lst)
            : elem{ new T[lst.size()] }, sz{ static_cast<int>(lst.size()) }
        {
            std::copy(lst.begin(), lst.end(), elem);
        }
        ~Vector() { 
            std::cout << "destroy\n";
            if (elem == nullptr) return;
            delete[] elem; 
        }
        
        Vector(const Vector& a) // copy constructor
            : elem { new T[a.sz] }, sz{ a.sz }
        {
            std::cout << "copy constructor\n";
            for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        }
        Vector& operator=(const Vector& lval) // copy assignment
        {
            std::cout << "copy assignment\n";
            T *rval = new T[lval.sz];
            for (int i = 0; i != lval.sz; ++i) rval[i] = lval.elem[i];
            delete[] elem;
            elem = rval;
            sz = lval.sz;
            return *this;
        }

        Vector(Vector&& rval) // move constructor
            : elem { rval.elem }, sz{ rval.sz }
        {
            std::cout << "move constructor\n";
            rval.elem = nullptr;
            rval.sz = 0;
        }
        Vector& operator=(Vector&& rval) // move assignment
        {
            std::cout << "move assignment\n";
            elem = std::move(rval.elem); // vacates rval
            this->sz = rval.sz;
            rval.elem = nullptr;
            rval.sz = 0;
            return *this;
        }

#if 1
        // this requires a move operation
        // lval is implicitly "this"
        Vector operator+(Vector& rval)
        {
            if (this->size() != rval.size()) throw std::length_error("Vector::operator+");

            Vector res(rval.size());
            for (int i = 0; i != rval.sz; ++i) res[i] = this->elem[i] + rval[i];

            return res;
        }
#endif

        // support for range for looping
        T *begin()
        {
            return this->size() ? &this->elem[0] : nullptr;
        }
        T *end()
        {
            return begin() + this->size();
        }

        void resize(int n) 
        {
            delete[] elem;
            elem = new T[n];
            sz = n;
            for (int i = 0; i != size(); ++i)  elem[i] = 0;
        }
        T& operator[] (int i) override
        { 
            if (i < 0 || size() <= i)
                throw std::out_of_range("Vector::operator[]");
            return elem[i]; 
        }
        int size() const noexcept override { return sz; }
        void show() const override
        {
            std::cout << "show: Vector\n";
            for (int i = 0; i != size(); ++i) {
                std::cout << elem[i] << std::endl;
            }
        }
    private:
        T *elem;
        int sz;
    };

#if 0
    // must be non-member if using 2 parameters
    Vector operator+(Vector& lval, Vector& rval)
    {
        std::cout << "Vector operator+\n";
        if (rval.size() != lval.size()) throw std::length_error("Vector::operator+");
        Vector res(lval.size());
        for (int i = 0; i != rval.size(); ++i) res[i] = rval[i] + lval[i];
        return res;
    }
#endif

    template <typename T>
    class List : public Container<T> {
    public:
        List(int s) :elem{ new T[s] }, sz{ s } 
        {
            for (int i = 0; i != sz; ++i)  elem[i] = 0;
        }

        List(const List& a) // copy constructor
            : elem { new T[a.sz] }, sz{ a.sz }
        {
            std::cout << "copy constructor\n";
            for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        }
        List& operator=(const List& lval) // copy assignment
        {
            std::cout << "copy assignment\n";
            T *rval = new T[lval.sz];
            for (int i = 0; i != lval.sz; ++i) rval[i] = lval.elem[i];
            delete[] elem;
            elem = rval;
            sz = lval.sz;
            return *this;
        }

        List(List&& rval) // move constructor
            : elem { rval.elem }, sz{ rval.sz }
        {
            std::cout << "move constructor\n";
            rval.elem = nullptr;
            rval.sz = 0;
        }
        List& operator=(List&& rval) // move assignment
        {
            std::cout << "move assignment\n";
            elem = std::move(rval.elem); // vacates rval
            this->sz = rval.sz;
            rval.elem = nullptr;
            rval.sz = 0;
            return *this;
        }
        
        ~List() { delete[] elem; }
        T& operator[] (int i) override { return elem[i]; }

        // support for range for looping
        T *begin()
        {
            return this->size() ? &this->elem[0] : nullptr;
        }
        T *end()
        {
            return begin() + this->size();
        }

        int size() const override { return sz; };
        void show() const override
        {
            std::cout << "show: List\n";
            for (int i = 0; i != size(); ++i) {
                std::cout << elem[i] << std::endl;
            }
        }
    private:
        T *elem;
        int sz;
    };

    template <typename T>
    class Array { // : public Container {
    public:
        Array(int s) :elem{ new T[s] }, sz{ s } 
        {
            for (int i = 0; i != sz; ++i)  elem[i] = 0;
        }

        Array(std::initializer_list<T> lst)
            : elem{ new T[lst.size()] }, sz{ static_cast<int>(lst.size()) }
        {
            std::copy(lst.begin(), lst.end(), elem);
        }

        Array(const Array& a) // copy constructor
            : elem { new T[a.sz] }, sz{ a.sz }
        {
            std::cout << "copy constructor\n";
            for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        }
        Array& operator=(const Array& lval) // copy assignment
        {
            std::cout << "copy assignment\n";
            T *rval = new T[lval.sz];
            for (int i = 0; i != lval.sz; ++i) rval[i] = lval.elem[i];
            delete[] elem;
            elem = rval;
            sz = lval.sz;
            return *this;
        }

        Array(Array&& rval) // move constructor
            : elem { rval.elem }, sz{ rval.sz }
        {
            std::cout << "move constructor\n";
            rval.elem = nullptr;
            rval.sz = 0;
        }
        Array& operator=(Array&& rval) // move assignment
        {
            std::cout << "move assignment\n";
            elem = std::move(rval.elem); // vacates rval
            this->sz = rval.sz;
            rval.elem = nullptr;
            rval.sz = 0;
            return *this;
        }
        
        ~Array() { delete[] elem; }
        T& operator[] (int i) { return elem[i]; }

        // support for range for looping
        double *begin()
        {
            return this->size() ? &this->elem[0] : nullptr;
        }
        double *end()
        {
            return begin() + this->size();
        }

        int size() const { return sz; };
        void show() const
        {
            std::cout << "show: Array\n";
            for (int i = 0; i != size(); ++i) {
                std::cout << elem[i] << std::endl;
            }
        }
    private:
        T *elem;
        int sz;
    };

    template <typename T, int N>
    struct Buffer {
        using value_type = T;
        constexpr int size() { return N; }
        T elem[N];
    };
}

template <typename T>
double read_and_sum(int s)
{
    troll::Vector<T> v(s);
    double sum;

    try {

        for (int i = 0; i != v.size(); ++i) 
            std::cin >> v[i];
    
        sum = 0;
        for (int i = 0; i != v.size(); ++i)
            sum += v[i];

        std::cout << v[9];

    } catch (std::out_of_range) {
        std::cout << "out of range dude\n";
        // we can rethrow
        // throw;
        // or terminate();
    }

    return sum;
}

template <typename T>
void use2(troll::Vector<T> v)
{
}

template <typename T>
void use(troll::Container<T>& c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i) {
        std::cout << c[i] << std::endl;
    }
}

template <typename C, typename T, typename Oper>
T for_all(C& c, T& t, Oper op)
{
    T acc = t; // initial value
    for (auto& s : c) {
        op(s); //acc += s;
    }
    return acc;
}

template <typename T>
std::unique_ptr<troll::Container<T>> factory(troll::Type t, int sz)
{
    switch (t) {
        case troll::Type::Vector:
            return std::unique_ptr<troll::Container<T>>{ new troll::Vector<T>(sz)};
        case troll::Type::List:
            return std::unique_ptr<troll::Container<T>>{ new troll::List<T>(sz)};
    }
    return nullptr;
}

template <typename T>
void iterate(const std::vector<std::unique_ptr<troll::Container<T>>>& vc)
{
    for (auto& p : vc) { // needs copy constructor
#if 0 // broken
        if (std::unique_ptr<troll::Vector> pv = dynamic_cast<std::unique_ptr<troll::Vector>>(p)) {
            std::cout << "got a Vector ...\n";
        }
        if (std::unique_ptr<troll::List> pl = dynamic_cast<std::unique_ptr<troll::List>>(p)) {
            std::cout << "got a List ...\n";
        }
#endif
        p->show();
    }
}

#include <regex>
#include <fstream>
void search_file(std::string file_name, std::regex pat)
{
    std::ifstream in(file_name);
    if (!in) {
        std::cerr << "no such file: " << file_name << '\n';
        return;
    }
    int lineno = 0;
    for (std::string line; getline(in, line); ) {
        ++lineno;
        std::smatch matches;
        if (std::regex_search(line, matches, pat)) {
            std::cout << "line: " << lineno << ": " << matches[0] << '\n';
            if (matches.size() > 1 && matches[1].matched) {
                std::cout << "\t: " << matches[1] << '\n';
            }
        }
    }
}

troll::Vector2 make()
{
    troll::Vector2 tmp = {42,43,44};
    return tmp;
}

int main()
{
    //std::cout << read_and_sum(6) << std::endl;
    static_assert(sizeof(int) <= 4, "ints are too small");

    troll::Complex a, b;

    troll::Vector<double> v1 = {1,2,3,4};
    //troll::Vector v2 = 4; // explicit so not ok, defines v(4);
    troll::Vector<double> v2 = {1,2,3,4};
    troll::Vector<double> v3 = {1,2,3,4};
    use(v1); // polymorphic function
    use2(v1); // copy constructor
    v1.show();
    v1.resize(4);
    v1.show();
    v1 = v2; // copy assignment
    std::cout << "doing add\n";
    v3 = v1 + v2; //broken
    use(v3);

    std::vector<std::unique_ptr<troll::Container<double>>> vc;
    vc.push_back(factory<double>(troll::Type::Vector, 6));
    vc.push_back(factory<double>(troll::Type::List, 4));
    iterate(vc);

    troll::Array<double> r = {3, 6, 9, 12};
    r.show();

    std::cout << "auto for\n";
    for (auto& s : r) {
        std::cout << s << std::endl;
    }
    for (auto& s : v1) {
        std::cout << s << std::endl;
    }

    troll::Buffer<char,8> buf1 = {'a','b','c','d','e','f','g','h'};
    //troll::Buffer<char,8> buf2 = "abcdefgh";
    for (int i = 0; i < buf1.size(); ++i) {
        std::cout << "[" << i << "] : " << buf1.elem[i] << std::endl;
    }

    // use a lambda to pass a visitor function
    std::vector<int> vi = {42,17,33,197,56};
    int vv = 42;
    for_all(vi, vv,[](int v){std::cout << "dude: " << v << std::endl;});

    // TX 77845
    std::regex pat {R"(\w{2}\s*\d{5}(-\d{4})?)"};
    search_file("basics.cpp", pat);

    std::cout << "move demo\n";
    std::vector<int> nm1 = {1,2,3};
    std::vector<int> nm2;
    for (auto& n : nm1) std::cout << n << std::endl;
    nm2 = std::move(nm1);
    std::cout << "move demo - empty\n";
    for (auto& n : nm1) std::cout << n << std::endl;
    std::cout << "move demo - recipient\n";
    for (auto& n : nm2) std::cout << n << std::endl;

    troll::Vector2 dv(3);
    troll::Vector2 dv2(dv);
    troll::Vector2 dv3 = {1,2,3};
    dv3.show();
    dv.show();
    dv2 = dv3;
    dv2.show();

    dv2 = make(); // move assignment
    dv2[2] = 137; // demo mutating vector using operator[]
    dv2.show();

    
    double sum = 0.0;
    for (int i = 0; i < dv2.size(); ++i) {
        sum += dv2.at(i);
    }
    std::cout << "sum: " << sum << std::endl;
    
    // or
    sum = 0.0;
    for (int i = 0; i < dv2.size(); ++i) {
        sum += dv2[i]; // using operator[]
    }
    std::cout << "sum: " << sum << std::endl;
    
    troll::Vector2 dv4(std::move(make())); // move ctor
    troll::Vector2 dv5(std::move(dv2)); // move ctor - steal dv2
    troll::Vector2 dv6 = std::move(dv4); // swap dv4 and dv6
    dv4.show(); // empty, totally vacated
    dv5.show();
    dv6.show();

}

