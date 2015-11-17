#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person;
std::istream &read(std::istream &is, Person &person);

class Person {

friend std::istream &read(std::istream &is, Person &person);
friend std::ostream &print(std::ostream &os, const Person &person);

public:
    Person() = default;
    Person(const std::string n, const std::string a) : addr(a), nm(n) {}
    Person(std::istream &is) { read(is, *this); }
    std::string name() const { return nm; }
    std::string address() const { return addr; }

private:
    std::string nm;
    std::string addr;
};

std::istream &read(std::istream &is, Person &person) {
    is >> person.nm >> person.addr;
    return is;
}

std::ostream &print(std::ostream &os, const Person &person) {
    os << person.name() << "\t" << person.address(); 
    return os;
}


#endif

