#include <initializer_list> 
#include <iostream> 

int main()
{
    std:: initializer_list <int> list = { 1,2,3,4,5 }; 
    std:: cout << "size = " << list.size() << std:: endl; // all values with range for loop 
    for (auto val : list) { 
        std:: cout << val << "-"; 
    } 

    std:: cout << std:: endl; // all values with standard loop 
    for (auto iter = list.begin(); iter != list.end(); ++iter) { 
        std:: cout << *iter << "_"; 
    } 
    std:: cout << std:: endl;

}
