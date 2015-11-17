#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include <set>
#include "Message.h"

class Message;
class Folder {
    friend class Message;
public:
    void addMsg(Message* m){
        messages.insert(m);
    }
    void remMsg(Message* m){
        messages.erase(m);
    }

    void show() {
        for (auto m : messages) 
            std::cout << "[]: " << m->get_contents() << std::endl;
    }

private:
    std::set<Message*> messages;
};



#endif

