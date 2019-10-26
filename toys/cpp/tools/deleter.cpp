#include <iostream>
#include <memory>


using std::cout; using std::endl;
using std::shared_ptr;


struct tester {
    int i;
};

/* deleter function */
void end_tester(tester *t) {
    cout << "called end_tester\n";
}

void test_deleter() {
    tester t;
    cout << "creating tester shared pointer...\n";
    shared_ptr<tester> pt(&t, end_tester);
    cout << "tester shared pointer going out of scope here...\n";
 }

void test_deleter_lambda() {
    tester t;
    auto h = [](tester *t)->void{cout << "called end_tester lambda\n";};
    cout << "creating tester shared pointer...\n";
    shared_ptr<tester> pt(&t, h);
    cout << "tester shared pointer going out of scope here...\n";
}

int main()
{
    //test_deleter();
    test_deleter_lambda();
    return 0;
}
