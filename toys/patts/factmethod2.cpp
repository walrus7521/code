#include <iostream>
#include <memory>

using namespace std;

class Option
{
public:
    using Pointer = std::shared_ptr<Option>;
    virtual void Evaluate() = 0;
};

class Option1 : public Option
{
    virtual void Evaluate() { cout << "option1" << endl; }
};
class Option2 : public Option
{
    virtual void Evaluate() { cout << "option2" << endl; }
};
class Option3 : public Option
{
    virtual void Evaluate() { cout << "option3" << endl; }
};

enum class OptionType {
    OPTION1,
    OPTION2,
    OPTION3
};

Option* CreateOption(OptionType type) {
    Option *pOption = nullptr;
    switch (type) {
        case OptionType::OPTION1:
            pOption = new Option1();
            break;
        case OptionType::OPTION2:
            pOption = new Option2();
            break;
        case OptionType::OPTION3:
            pOption = new Option3();
            break;
    }
    return pOption;
}

int main()
{
    Option *po1 = CreateOption(OptionType::OPTION1);
    Option *po2 = CreateOption(OptionType::OPTION2);
    Option *po3 = CreateOption(OptionType::OPTION3);
    po1->Evaluate();
    po2->Evaluate();
    po3->Evaluate();
}

