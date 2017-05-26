#include "Vector_container.h"
#include <iostream>

#if 0

void use(Container& c) {
    const int sz = c.size();

   for (int i = 0; i != sz; ++i)
        c[i] = 'a' + i;
   for (int i = 0; i != sz; ++i)
        std::cout << c[i] << std::endl;

//   for (auto& x : c)
//       std::cout << x << std::endl;
       
}
#endif

void g() {
    Vector_container vc(10);
    //Container *pc = &vc;
    //use(*pc);
#if 0
    for (int i = 0; i != vc.size(); ++i)
        vc[i] = 'a' + i;
    for (int i = 0; i != vc.size(); ++i)
        std::cout << vc[i] << std::endl;
#endif
}

int main()
{
    //g();
    return 0;

}
