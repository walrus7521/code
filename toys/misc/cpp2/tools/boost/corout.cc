#if 0
// broken
#include <iostream>
#include <string>
#include <boost/coroutine/all.hpp>
#include <boost/coroutine/symmetric_coroutine.hpp>

using std::cout; using std::endl;
using std::string;

typedef boost::coroutines::symmetric_coroutine<string&(std::size_t max_chars_to_process)> corout_t;

void coroutine_task(corout_t::call_type& caller);

int main() {
    corout_t coroutine(coroutine_task);

//    coroutine(10);
//    strint &s = coroutine.get();

}

void coroutine_task(corout_t::call_type& caller) {
    string result;

    caller(42);

    //while (1) {
        std::size_t max_chars_to_process = caller.get();
    //    caller(result);
    //}
}
#endif
#if 0
// broken
#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/coroutine/coroutine.hpp>

// The coroutine type.
typedef boost::coroutines::coroutine<int()> coro;

// The implementation routine of the coroutine.
void xrange_impl(coro::caller_type& yield, int limit)
{
  for(int i = 0; i < limit; i++) {
    yield(i); // return results back to the caller
  }
}

int main()
{
  // Construct the coroutine instance
  coro xrange(boost::bind(xrange_impl, _1, 10000));

  int sum = 0;
  while(xrange) { // Check completion status
    sum += xrange.get(); // Extract yielded result
    xrange(); // Fire it again.
  }
  assert(sum == 49995000);
}
#endif
#if 0
// broken
#include <boost/coroutine/all.hpp>
#include <string>
#include <vector>

typedef boost::coroutines::coroutine<int(char)> coroutine_t;

void f(coroutine_t::caller_type & ca)
{
    std::vector<int> vec = {1, 2, 3};
    for (int i : vec)
    {
        char c = ca.get();
        std::cout << "c: " << c << std::endl;
        ca(i);
    }
}

int main()
{
    coroutine_t cr(f);
    std::string str("abc");
    for (char c : str)
    {
        std::cout << c << std::flush;
        cr(c);
        int n = cr.get();
        std::cout << n << std::endl;        
    }
}
#endif
#if 0
// working
#include <boost/coroutine/all.hpp>
#include <iostream>

using namespace boost::coroutines;

void cooperative(coroutine<void>::push_type &sink)
{
    std::cout << "Hello";
    sink();
    std::cout << "world";
}

int main()
{
    coroutine<void>::pull_type source{cooperative};
    std::cout << ", ";
    source();
    std::cout << "!\n";
}
#endif
#if 1
// working
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>

typedef boost::coroutines::symmetric_coroutine< void >  coro_t;

coro_t::call_type * c1 = 0;
coro_t::call_type * c2 = 0;

void foo( coro_t::yield_type & yield)
{
    std::cout << "foo1" << std::endl;
    yield( * c2);
    std::cout << "foo2" << std::endl;
    yield( * c2);
    std::cout << "foo3" << std::endl;
}

void bar( coro_t::yield_type & yield)
{
    std::cout << "bar1" << std::endl;
    yield( * c1);
    std::cout << "bar2" << std::endl;
    yield( * c1);
    std::cout << "bar3" << std::endl;
}

int main( int argc, char * argv[])
{
    coro_t::call_type coro1( foo);
    coro_t::call_type coro2( bar);
    c1 = & coro1;
    c2 = & coro2;
    coro1();
    std::cout << "Done" << std::endl;

    return EXIT_SUCCESS;
}
#endif
