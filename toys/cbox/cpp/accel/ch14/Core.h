#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>
#include <vector>

class Core {
    friend class Student_info;
//    friend class Handle<Core>;
public:
    Core(): midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }

    std::string name() const;

    virtual std::istream& read(std::istream&);
    virtual double grade() const;

    virtual ~Core() { }

    virtual Core* clone() const { return new Core(*this); }

protected:
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

private:
    std::string n;
};

bool compare(const Core& c1, const Core& c2)
{
    return c1.name() < c2.name();
}

#if 0
bool compare_Core_ptrs(const Core* cp1, const Core* cp2)
{
    return compare(*cp1, *cp2);
}

bool compare_Core_handles(const Handle<Core>& s1, const Handle<Core>& s2)
{
    return s1->name() < s2->name();
}

bool compare_Core_Ref_handles(const Ref_handle<Core>& s1, const Ref_handle<Core>& s2)
{
    return s1->name() < s2->name();
}
#endif

bool compare_Core_Ptrs(const Ptr<Core>& s1, const Ptr<Core>& s2)
{
    return compare(*s1, *s2);
}

double grade(double mid, double fin, std::vector<double> hw)
{
    return 42.0;
}

std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
    if (in) {
        in.clear();
        double x;
        while (in >> x)
            hw.push_back(x);
        in.clear();
    }
    return in;
}

std::string Core::name() const { return n; }

double Core::grade() const
{
    return ::grade(midterm, final, homework);
}

std::istream& Core::read_common(std::istream& in)
{
    in >> n >> midterm >> final;
    return in;
}

std::istream& Core::read(std::istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

#endif
