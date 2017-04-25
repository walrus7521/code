/*
How do I serialize objects that aren’t part of an inheritance hierarchy and 
that don’t contain pointers to other objects?  
This is the least sophisticated problem, and not surprisingly, it is also the 
least sophisticated solution:

Every class should handle its own serialization and unserialization. You will 
typically create a member function that serializes the object to some sink 
(such as a std::ostream), and another that allocates a new object, or perhaps 
changes an existing object, setting the member data based on what it reads from 
some source (such as a std::istream).
If your object physically contains another object, e.g., a Car object might have 
a member variable of type Engine, the outer object’s serialize() member function 
should simply call the appropriate function associated with the member object.
Use the primitives described earlier to read/write the simple types in text or 
binary format.
If a class’s data structure might change someday, the class should write out a 
version number at the beginning of the object’s serialized output. Unless you 
are absolutely sure that there is no possible chance of the data structure 
changing at any point in the future, do yourself a favor and include the version 
number now. It is much easier to put in a version number from the very beginning 
than to add one later when you have an unanticipated data structure change. The 
version number simply represents the serialized format; it should not get 
incremented simply when the class’s behavior changes. This means the version 
numbers don’t need to be fancy — they usually don’t need a major and minor number.

*/
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

//typedef std::tuple<std::string, int> field_type;

template <typename T, typename V>
class OBJECT{ // The object to be serialized / deserialized
public:
  // Members are serialized / deserialized in the order they are declared. Can use bitpacking as well.
    T member1;
    T member2;
    V member3;
    V member4;
};

template <typename T, typename V>
void write(const std::string& file_name, OBJECT<T, V>& data) // Writes the given OBJECT data to the given file name.
{
    std::ofstream out;
    out.open(file_name,std::ios::binary);
    out.write(reinterpret_cast<char*>(&data), sizeof(OBJECT<T, V>));
    out.close();
};

template <typename T, typename V>
void read(const std::string& file_name, OBJECT<T, V>& data) // Reads the given file and assigns the data to the given OBJECT.
{
    std::ifstream in;
    in.open(file_name,std::ios::binary);
    in.read(reinterpret_cast<char*>(&data), sizeof(OBJECT<T, V>));
    in.close();
};

template <typename T, typename V>
void show(OBJECT<T, V>& data) // Reads the given file and assigns the data to the given OBJECT.
{
    std::cout << "member1: " << data.member1 << std::endl;
    std::cout << "member2: " << data.member2 << std::endl;
    std::cout << "member3: " << data.member3 << std::endl;
    std::cout << "member4: " << data.member4 << std::endl;
}

int main()
{
    OBJECT<int, std::string> o;
    o.member1 = 42;
    o.member2 = 43;
    o.member3 = "dude";
    o.member4 = "wusup";
    write("test.txt", o);
    OBJECT<int, std::string> o2;
    read("test.txt", o2);
    show(o2);
}

