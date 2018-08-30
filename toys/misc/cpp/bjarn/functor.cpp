#include <iostream>
#include <string>
#include <regex>
#include <list>

using std::list;
using std::vector;
using std::string;
using std::cerr;
using std::cin;
using std::cout;

template<typename T>
class Less_than {
    const T val;
public:
    Less_than(const T& v) :val(v) {}
    bool operator()(const T& x)const { return x<val; }
};


Less_than<int> lti{42};
Less_than<std::string> lts{"Backus"};

 void fct(int n, const std::string &s)
{
    bool b1 = lti(n);
    bool b2 = lts(s);
    std::cout << "lti(" << n << ") = " << b1 << std::endl;
    std::cout << "lts(" << s << ") = " << b2 << std::endl;
    if (b1) std::cout << "lti(" << n << ") is less than" << std::endl;
    else    std::cout << "lti(" << n << ") is greater than" << std::endl;
    if (b2) std::cout << "lts(" << s << ") is less than" << std::endl;
    else    std::cout << "lts(" << s << ") is greater than" << std::endl;
}

template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f1(const std::vector<int>& vec, const std::vector<std::string>& lst, int x, const std::string& s)
{
    std::cout << "number of values less than " << x
        << ": " << count(vec, Less_than<int>{x}) << '\n';
    std::cout << "number of values less than " << s 
        << ": " << count(lst, Less_than<std::string>{s}) << '\n';
}

void f2(const std::vector<int>& vec, const std::vector<std::string>& lst, int x, const std::string& s)
{
    std::cout << "number of values less than " << x
        << ": " << count(vec, [&](int a){ return a<x; }) << '\n';
    std::cout << "number of values less than " << s 
        << ": " << count(lst, [&](const std::string& a){ return a<s; }) << '\n';
}

template<typename C, typename Oper>
void for_all(C& c, Oper op)
{
    for (auto x : c)
        op(x);
}

class Point {
public:
    Point(int x, int y) {p_x = x; p_y = y;}
private:
    int p_x, p_y;
};

enum class Kind { circle, triangle, smiley };

class Shape {
public:
    virtual Point center() const = 0;
    virtual void move(Point to) = 0;
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;
    virtual ~Shape(){}
};

class Circle : public Shape {
public:
    Circle(Point p, int rr);

    Point center() const { return x; }
    void move(Point to) { x = to; }
    void draw() const {};
    void rotate(int a) { r += a; }
private:
    Point x;
    int r;
};

#if 0
Shape *read_shape(std::istream& is)
{
    int length = 32;
    char * buffer = new char [length];    
    std::vector<std::unique_ptr<Shape>> v;
    is.read (buffer,length);
    Circle *cp = new Circle(Point(0, 4), 7);

    return nullptr; //cp;
}
#endif

void user()
{
//    while (std::cin) {
//        Shape *sp = read_shape(std::cin);
//        v.push_back(sp);
//    }
//    for_all(v,[](Shape& s){ s.draw(); });
//    for_all(v,[](Shape& s){ s.rotate(45); });
}

void user2()
{
    std::vector<int> vi {1,2,3,4,5,6};
    for_all(vi,[](int i){ std::cout << i << std::endl; });
}

template<typename T>
using iterator = typename T::iterator;

template<typename C, typename V>
vector<iterator<C>> find_all(C& c, V v)
{
    vector<iterator<C>> res;
    for (auto p = c.begin(); p!= c.end(); ++p)
        if (*p == v)
            res.push_back(p);
    return res;
}

void test()
{
    string m{"Mary had a little lamb"};
    for (auto p : find_all(m,'a')) { // p is a string::iterator
        if (*p!='a')
            cout << "string bug!\n";
        else
            cout << "string is good!!\n";
    }
#if 0
    list<double> ld1{1.1,2.2,3.3,1.1};
    for (auto p : find_all(ld1, 1.1)) {
        if (*p!=1.1)
            cout << "list1 bug!\n";
        else
            cout << "list1 is good!!\n";
    }
#endif
    list<double> ld2{1.2,2.2,3.3,1.4};
    for (auto p : find_all(ld2, 1.2)) {
        if (*p!=1.2)
            cout << "list2 bug!\n";
        else
            cout << "list2 is good!!\n";
    }

    vector<string> vs{"red", "blue", "green", "green", "orange", "green"};
    for (auto p : find_all(vs,"red")) {
        if (*p!="red")
            cout << "vector bug!\n";
        else
            cout << "vector is good!!\n";
    }

}

int main ()
{
    user2();
    fct(88, "Babs");
    test();
    return 0;
}
