#include <iostream>
#include "Message.h"

int main() 
{
    Folder f1("dogs");
    Folder f2("cats");
    Message m1("yo sup");
    Message m2("dude");
    Message m3("hooda homi");
    Message m4("ooyaa");
    m1.save(f1);
    m2.save(f1);
    m3.save(f1);
    m4.save(f1);
    m2.save(f2);
    f1.show();
    f2.show();
    return 0;
}
