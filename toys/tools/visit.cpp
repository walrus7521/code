#include <iostream>

using namespace std;

class Visitable;

class Visitor
{
private:
    friend class Visitable;
    virtual void OnVisit(Visitable& visitable) = 0;
};

class Visitable
{
public:
    virtual ~Visitable(){}
    void Visit(Visitor& visitor) {
        visitor.OnVisit(*this);
    }
};

class Option : public Visitable
{
public:
    virtual void Evaluate() = 0; //{ cout << "eval" << endl; }
};

class Option1 : public Option
{
public:
    virtual void Evaluate(){ cout << "eval1" << endl; }
};
class Option2 : public Option
{
public:
    virtual void Evaluate(){ cout << "eval2" << endl; }
};
class Option3 : public Option
{
public:
    virtual void Evaluate(){ cout << "eval3" << endl; }
};

class EvaluateVisitor : public Visitor
{
public:
    virtual void OnVisit(Visitable& visitable) {
        Option *pOption = dynamic_cast<Option*>(&visitable);
        if (pOption != nullptr) {
            pOption->Evaluate();
        }
    }
};

int main()
{
    Option1 o1;
    Option2 o2;
    Option3 o3;
    EvaluateVisitor eval;
    eval.OnVisit(o1);
    eval.OnVisit(o2);
    eval.OnVisit(o3);
}
