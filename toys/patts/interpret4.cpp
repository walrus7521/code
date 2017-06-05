#include <iostream>
#include <list>

using namespace std;

class Context
{
};
 
class AbstractExpression
{
public:
    virtual void Interpret(Context *context) = 0;
};
 
class TerminalExpression : public AbstractExpression
{
public:
    void Interpret(Context *context) {
        cout << "Called Terminal.Interpret()" << endl;
    }
};
 
class NonterminalExpression : public AbstractExpression
{
public:
    void Interpret(Context *context) {
        cout << "Called Nonterminal.Interpret()" << endl;
    }
};
 
int main() {
    Context *context = new Context();
 
    // Usually a tree 
    list<AbstractExpression*> alist; // = new list<AbstractExpression*>();

    // Populate 'abstract syntax tree' 
    alist.push_back(new TerminalExpression());
    alist.push_back(new NonterminalExpression());
    alist.push_back(new TerminalExpression());
    alist.push_back(new TerminalExpression());
 
    // Interpret
    for (auto& exp : alist) {
        exp->Interpret(context);
    }
}
 

