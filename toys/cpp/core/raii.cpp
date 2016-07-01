#include <iostream>
#include <string>

using namespace std;

class Socket {
public:
    Socket(const string& hostname) {}
};

// the dtor will be called, even if an exception is raised.
class HttpRequest {
public:
    HttpRequest(const string& hostname) :
        sock_(new Socket(hostname)){
            cout << "ctor" << endl; }
    void send(string soapMsg) { 
        /*sock_ << soapMsg;*/ 
        cout << soapMsg << endl;
    }
    ~HttpRequest() { 
        delete sock_; 
        cout << "dtor" << endl; }
private:
    Socket *sock_;
};

void sendMyData(string soapMsg, string host) {
    HttpRequest req(host);
    req.send(soapMsg);
}

int main() {
    string s = "xml";
    sendMyData(s, "www.oreilly.com");
}
