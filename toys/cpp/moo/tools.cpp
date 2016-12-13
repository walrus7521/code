#include <iostream>
#include <string>
#include <exception>

// exception handling
class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(const std::string &s)
        : std::logic_error(s) {}
    isbn_mismatch(const std::string &s,
            const std::string &lhs, const std::string &rhs) 
        : std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};

using namespace std;

void excepts()
{
    // see Blob for function try block
    string isbn = "123";
    string left = "left";
    string right = "right";
    try {
        throw isbn_mismatch("wrong isbns", left, right);
    } catch (const isbn_mismatch &e) {
        cerr << e.what() << ": left isbn(" << e.left 
             << ") right isbn(" << e.right << ")" << endl;
    }
}

namespace dookie {
    inline namespace dookie_latest { // default (unqualified)
        int dookestr(int n) { cout << "latest dook: " << n << endl; return n; }
    }
    namespace dookie_ver1 {
        int dookestr(int n) { cout << "ver1 dook: " << n << endl; return n; }
    }
}

using namespace dookie;

void namespaces()
{
    dookestr(42); // requires using
    dookie::dookie_ver1::dookestr(42); // requires using
}

int main()
{
    //excepts();
    namespaces();
}
