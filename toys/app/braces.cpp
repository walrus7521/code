#include <iostream>
#include <stack>

using namespace std;

int main()
{
    char expr[]="{([])}[]";
    stack<char> s;
    char a, b, c;
    int level = 0;
    //Traversing the Expression
    for (int i = 0; i < strlen(expr); i++) {
        if(expr[i]=='('||expr[i]=='['||expr[i]=='{') {
              //Push the element in the stack
              s.push(expr[i]);
              level++;
        } else {
            switch(expr[i]) {
            case ')':
                //Store the top element in a
                a=s.top();
                s.pop();
                if(a=='{'||a=='[')
                    cout<<"Not Balanced\n";
                level--;
                break;
            case '}':
                //Store the top element in b
                b=s.top();
                s.pop();
                if(b=='('||b=='[')
                    cout<<"Not Balanced\n";
                level--;
                break;
            case ']':
                //Store the top element in c
                c=s.top();
                s.pop();
                if(c=='('||c=='{')
                    cout<<"Not Balanced\n";
                level--;
                break;
            }
        }
        cout << "level: " << level << endl;
    }
    //Check Empty Stack
    if(s.empty())
    cout<<"Balanced\n";
    else
    cout<<"Not Balanced\n";
    return 0;
}
