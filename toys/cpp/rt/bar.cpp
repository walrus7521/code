#include <iostream>
#include <string>
#include <cstdint>
#include <unistd.h>

class bar_base
{
public:
    virtual void toggle() = 0;  // pure abstract
    // virtual destructor, ensures derived destructors are called
    virtual ~bar_base(){}

    // interface for querying bar state
    bool state_is_on() const { return is_on; }

protected:
    bool is_on;

    // a protected default constructor
    // ensures no base classes can be instantiated alone,
    // only as part of a derived class
    bar_base() : is_on(false){}

private:
    // private non-implemented copy constructor
    bar_base(const bar_base&) = delete;

    // private non-implemented copy assignment constructor
    const bar_base& operator=(const bar_base&) = delete;

};

// implement 2 types of bars: port & star
class bar_port : public bar_base
{
public:
    typedef std::uint8_t port_type;
    typedef std::uint8_t bval_type;

    bar_port(const port_type p,
             const bval_type b) : port(p),
                                  bval(b)
    {
    }

    virtual ~bar_port(){}

    // using optional virtual keyword here to remind me 
    // this is an override
    virtual void toggle()
    {
        std::cout << "toggle bar_port: " << port << std::endl;
        is_on = !is_on;
    }

private:
    const port_type port;
    const bval_type bval;

};

class star
{
public:
    explicit star() : shine(42U) {}
    ~star(){}

    void set_shine(const std::uint8_t shine)
    {
        this->shine = std::min<std::uint8_t>(shine, 100U);
    }

    std::uint32_t get_shine()
    {
        return shine;
    }
private:
    std::uint32_t shine;
};

class bar_star : public bar_base
{
public:
    explicit bar_star(star *s) : my_star(s) {}
    virtual ~bar_star(){}

    virtual void toggle()
    {
        std::cout << "toggle bar_star: " << my_star->get_shine() << std::endl;
    }

    void dim()
    {
    }

private:
    star *my_star;
};

namespace
{
    bar_port bp0
    {
        'b',
        'a'
    };
    star s {};
    bar_star bs0
    {
        &s
    };
}

constexpr uint32_t one_second = 1000000;
int main()
{
    // toggle led_b5 forever
    for (;;)
    {
        bp0.toggle();
        bs0.toggle();
        usleep(one_second);
    }
}



