#include <iostream>
#include <string>
#include <cstdint>
#include <unistd.h>

template <typename port_type,
          typename bval_type,
          const port_type port,
          const bval_type bval>
class foo
{
public:

    foo()
    {
        std::cout << std::hex << "port: " << port << std::endl;
        std::cout << "bval: " << bval << std::endl;
    }

    static void toggle() //const
    {
        std::cout << std::hex << "toggle: " << pdir << std::endl;
    }

private:
    static constexpr port_type pdir = ~port;
};

namespace
{
    const foo<std::uint32_t,
              std::uint8_t,
              0x42,
              'b'> foo_t1;
}

constexpr uint32_t one_second = 1000000;
int main()
{
    // toggle led_b5 forever
    for (;;)
    {
        foo_t1.toggle();
        usleep(one_second);

    }
}



