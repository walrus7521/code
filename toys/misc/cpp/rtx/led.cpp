#include <iostream>
#include <cstdint>
#include <unistd.h>
#include "mcal_reg.h"

template <typename port_type,
          typename bval_type,
          const port_type port,
          const bval_type bval>
class led_template
{
public:
    //typedef std::uint8_t port_type;
    //typedef std::uint8_t bval_type;

    // constructor
    led_template()
    {
        std::cout << port << std::endl;
        std::cout << bval << std::endl;
        // set port pin to low
        //*reinterpret_cast<volatile bval_type*>(port)
        //    &= static_cast<bval_type>(~bval);

        // set the port pin direction to output
        //*reinterpret_cast<volatile bval_type*>(port - 1U)
        //    |= bval;
    }

    static void toggle() //const
    {
        //*reinterpret_cast<volatile bval_type*>(port)
        //    ^= bval;
        std::cout << "toggle: " << pdir << std::endl;
    }

private:
    static constexpr port_type pdir = port - 1U;
    //const port_type port;
    //const bval_type bval;
};

namespace
{
    // create led_b5 on portb.5
    const led_template<std::uint8_t,
                       std::uint8_t,
                       mcal::reg::portb,
                       mcal::reg::bval5> led_b5;
}

constexpr uint32_t one_second = 1000000;
int main()
{
    // toggle led_b5 forever
    for (;;)
    {
        led_b5.toggle();
        usleep(one_second);

    }
}



