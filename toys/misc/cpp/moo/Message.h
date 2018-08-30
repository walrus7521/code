#ifndef MESSAGE_H
#define MESSAGE_H

#include <set>
#include <string>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message &lhs, Message &rhs);

public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str = ""): contents(str) {}
    // copy control to manage pointers to this Message
    Message(const Message&);
    Message& operator=(const Message&);
    Message(Message&&);
    Message& operator=(Message&&);
    ~Message();
    // add/remove this Message from the specified Folder's set of messages
    void save(Folder&);
    void remove(Folder&);
    std::string get_contents() {
        return contents;
    }

private:
    std::string contents; // actual message
    std::set<Folder*> folders; // Folders that have this message
    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
    void move_Folders(Message *m);
};


class Folder {
    friend class Message;
public:
    Folder(const std::string nm = "") : name(nm) {}
    void addMsg(Message* m){
        messages.insert(m);
    }
    void remMsg(Message* m){
        messages.erase(m);
    }

    void show() {
        for (auto m : messages) 
            std::cout << "["<< name << "]: " << m->get_contents() << std::endl;
    }

private:
    std::set<Message*> messages;
    std::string name;
};


// copy constructor
Message::Message(const Message& rhs):
    contents(rhs.contents), folders(rhs.folders) {
    add_to_Folders(rhs);
}

// copy assignment
Message& Message::operator=(const Message& rhs) {
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

void Message::move_Folders(Message *m) {
    folders = std::move(m->folders);
    for (auto f : folders) {
        f->remMsg(m); // remove the old message from the Folder
        f->addMsg(this); // add this Message to that Folder
    }
    m->folders.clear(); // ensure destruction is harmless
}

Message::Message(Message &&rhs): contents(std::move(rhs.contents)) {
    move_Folders(&rhs);
}

Message& Message::operator=(Message &&rhs) {
    if (this != &rhs) {
        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder& f) {
    folders.insert(&f); // stores pointer
    f.addMsg(this);
}

void Message::remove(Folder& f) {
    folders.erase(&f); // removes pointer
    f.remMsg(this);
}

void Message::add_to_Folders(const Message& m) {
    for (auto f : m.folders) {
        f->addMsg(this);
    }
}

void Message::remove_from_Folders() {
    for (auto f : folders) {
        f->remMsg(this);
    }
    folders.clear();
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    for (auto f : lhs.folders) {
        f->remMsg(&lhs);
    }
    for (auto f : rhs.folders) {
        f->remMsg(&rhs);
    }
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders) {
        f->addMsg(&lhs);
    }
    for (auto f : rhs.folders) {
        f->addMsg(&rhs);
    }

}


#endif

