/*
 * This is example 5.5 "Multiple-readers-single-writer lock."
 *
 */

#include <cstdlib>
#include <map>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

struct user_info {
    std::string address;
    unsigned short age;
};

class users_online {
    typedef boost::shared_mutex         mutex_t;
    mutable mutex_t                     users_mutex_;
    std::map<std::string, user_info>    users_;

public:
    bool is_online(const std::string& username) const {
        boost::shared_lock<mutex_t> lock(users_mutex_);
        return users_.find(username) != users_.end();
    }

    unsigned short get_age(const std::string& username) const {
        boost::shared_lock<mutex_t> lock(users_mutex_);
        return users_.at(username).age;
    }

    void set_online(const std::string& username, user_info& data) {
        boost::lock_guard<mutex_t> lock(users_mutex_);
        users_.insert(std::make_pair(username, data));
    }

};

users_online g_uol;

void reader() {
    std::cout << "yo ho" << std::endl;
    if (g_uol.is_online("bart")) {
        unsigned short age = g_uol.get_age("bart");
        std::cout << "yo: " << age << std::endl;
    }
}

void writer() {
    //for (int i = 0; i < 16; i++) {
        struct user_info u; // = new struct user_info;
        u.address = "gig harbor";
        u.age = 56;
        g_uol.set_online("bart", u);
    //}
}

int main()
{
    boost::thread read1(&reader);
    boost::thread read2(&reader);
    boost::thread read3(&reader);

    boost::thread write1(&writer);
    //boost::thread write2(&writer);
    //boost::thread write3(&writer);

    write1.join();
    read1.join();
    read2.join();
    read3.join();

    //write2.join();
    //write3.join();

}
