#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

int main()
{
    char expr[] = "{([])}[]()";
    stack<char> s;
    char c;
    int level = 0;
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i]=='(' || expr[i]=='[' || expr[i]=='{') {
            s.push(expr[i]);
            level++;
        } else {
            switch (expr[i]) {
            case ')':
                c = s.top();
                s.pop();
                if (c=='{' || c=='[') cout<<"Not Balanced\n";
                level--;
                break;
            case '}':
                c = s.top();
                s.pop();
                if (c=='(' || c=='[') cout<<"Not Balanced\n";
                level--;
                break;
            case ']':
                c = s.top();
                s.pop();
                if (c=='(' || c=='{') cout<<"Not Balanced\n";
                level--;
                break;
            }
        }
        cout << "level: " << level << endl;
    }
    if (s.empty()) cout<<"Balanced\n";
    else cout<<"Not Balanced\n";
    return 0;
}
