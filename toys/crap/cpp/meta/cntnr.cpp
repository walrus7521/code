// http://eli.thegreenplace.net/2014/variadic-templates-in-c/

#include <iostream>
#include <vector>
#include <string>
#include <list>

template <template <typename, typename> class ContainerType,
          typename ValueType,
          typename AllocType>
void print_container(const ContainerType<ValueType, AllocType>& c) {
  for (const auto& v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}


int main()
{
    std::vector<double> vd{3.14, 8.1, 3.2, 1.0};
    print_container(vd);

    std::list<int> li{1, 2, 3, 5};
    print_container(li);
}
