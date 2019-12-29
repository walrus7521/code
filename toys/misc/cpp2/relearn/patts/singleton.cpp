#include <iostream>
#include <memory>

// the class to have only one instance
class Factory {
public:
    static std::shared_ptr<Factory> instance() {
        // static means only one, the first one
        static std::shared_ptr<Factory> instance(new Factory());
        return instance;
    }
private:
    // can't create instance directly
    Factory() {
        std::cout << "the one and only factory created" << std::endl;
    }
};

int main()
{
    std::shared_ptr<Factory> factory1 = Factory::instance();
    std::shared_ptr<Factory> factory2 = Factory::instance();
    std::shared_ptr<Factory> factory3 = Factory::instance();
}
