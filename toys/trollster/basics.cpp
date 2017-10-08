#include <iostream>
#include <stdexcept> // out_of_range
#include <vector>

namespace troll {
    enum class Type { Vector, List };

    // abstract type - pure interface
    class Container {
    public:
        virtual double& operator[] (int i) = 0;
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


    class Vector : public Container {
    public:
        Vector() :elem{ nullptr }, sz{ 0 } {}
        explicit Vector(int s) :elem{ new double[s] }, sz{ s } 
        {
            for (int i = 0; i != size(); ++i)  elem[i] = 0;
        }
        Vector(std::initializer_list<double> lst)
            : elem{ new double[lst.size()] }, sz{ static_cast<int>(lst.size()) }
        {
            std::copy(lst.begin(), lst.end(), elem);
        }
        ~Vector() { 
            std::cout << "destroy\n";
            if (elem == nullptr) return;
            delete[] elem; 
        }
        
        Vector(const Vector& a) // copy constructor
            : elem { new double[a.sz] }, sz{ a.sz }
        {
            std::cout << "copy constructor\n";
            for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        }
        Vector& operator=(const Vector& lhs) // copy assignment
        {
            std::cout << "copy assignment\n";
            double *rhs = new double[lhs.sz];
            for (int i = 0; i != lhs.sz; ++i) rhs[i] = lhs.elem[i];
            delete[] elem;
            elem = rhs;
            sz = lhs.sz;
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
        // lhs is implicitly "this"
        Vector operator+(Vector& rhs)
        {
            if (this->size() != rhs.size()) throw std::length_error("Vector::operator+");

            Vector res(rhs.size());
            for (int i = 0; i != rhs.sz; ++i) res[i] = this->elem[i] + rhs[i];

            return res;
        }
#endif

        void resize(int n) 
        {
            delete[] elem;
            elem = new double[n];
            sz = n;
            for (int i = 0; i != size(); ++i)  elem[i] = 0;
        }
        double& operator[] (int i) override
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
        double *elem;
        int sz;
    };

#if 0
    // must be non-member if using 2 parameters
    Vector operator+(Vector& lhs, Vector& rhs)
    {
        std::cout << "Vector operator+\n";
        if (rhs.size() != lhs.size()) throw std::length_error("Vector::operator+");
        Vector res(lhs.size());
        for (int i = 0; i != rhs.size(); ++i) res[i] = rhs[i] + lhs[i];
        return res;
    }
#endif

    class List : public Container {
    public:
        List(int s) :elem{ new double[s] }, sz{ s } 
        {
            for (int i = 0; i != sz; ++i)  elem[i] = 0;
        }

        List(const List& a) // copy constructor
            : elem { new double[a.sz] }, sz{ a.sz }
        {
            std::cout << "copy constructor\n";
            for (int i = 0; i != sz; ++i) elem[i] = a.elem[i];
        }
        List& operator=(const List& lhs) // copy assignment
        {
            std::cout << "copy assignment\n";
            double *rhs = new double[lhs.sz];
            for (int i = 0; i != lhs.sz; ++i) rhs[i] = lhs.elem[i];
            delete[] elem;
            elem = rhs;
            sz = lhs.sz;
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
        double& operator[] (int i) override { return elem[i]; }
        int size() const override { return sz; };
        void show() const override
        {
            std::cout << "show: List\n";
            for (int i = 0; i != size(); ++i) {
                std::cout << elem[i] << std::endl;
            }
        }
    private:
        double *elem;
        int sz;
    };

}

double read_and_sum(int s)
{
    troll::Vector v(s);
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

void use2(troll::Vector v)
{
}

void use(troll::Container& c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i) {
        std::cout << c[i] << std::endl;
    }
}

std::unique_ptr<troll::Container> factory(troll::Type t, int sz)
{
    switch (t) {
        case troll::Type::Vector:
            return std::unique_ptr<troll::Container>{ new troll::Vector(sz)};
        case troll::Type::List:
            return std::unique_ptr<troll::Container>{ new troll::List(sz)};
    }
    return nullptr;
}

void iterate(const std::vector<std::unique_ptr<troll::Container>>& vc)
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

int main()
{
    //std::cout << read_and_sum(6) << std::endl;
    static_assert(sizeof(int) <= 4, "ints are too small");

    troll::Complex a, b;

    troll::Vector v1 = {1,2,3,4};
    //troll::Vector v2 = 4; // explicit so not ok, defines v(4);
    troll::Vector v2 = {1,2,3,4};
    troll::Vector v3 = {1,2,3,4};
    use(v1); // polymorphic function
    use2(v1); // copy constructor
    v1.show();
    v1.resize(4);
    v1.show();
    v1 = v2; // copy assignment
    std::cout << "doing add\n";
    v3 = v1 + v2; //broken
    use(v3);

    std::vector<std::unique_ptr<troll::Container>> vc;
    vc.push_back(factory(troll::Type::Vector, 6));
    vc.push_back(factory(troll::Type::List, 4));
    iterate(vc);

}

