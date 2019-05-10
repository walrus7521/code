#include<iostream>
#include<string>
using namespace std;
// https://codereview.stackexchange.com/questions/133923/a-c-program-to-solve-a-rubiks-cube
//
class Solver
{
    private:
    string b;
    string c;
    string d;
    string e;
    string f;
    string g;
    string h;
    string i;
    string j;
    string k;
    string l;
    string n;
    string o;
    string p;
    string r;
    string s;
    string t;
    string u;
    string v;
    string w;
    string x;
    
    public:
    Solver();
    string getSol(char letter)
    {
        switch(letter)
        {
            case 'b': return b;
            case 'c': return c;
            case 'd': return d;
            case 'e': return e;
            case 'f': return f;
            case 'g': return g;
            case 'h': return h;
            case 'i': return i;
            case 'j': return j;
            case 'k': return k;
            case 'l': return l;
            case 'n': return n;
            case 'o': return o;
            case 'p': return p;
            case 'r': return r;
            case 's': return s;
            case 't': return t;
            case 'u': return u;
            case 'v': return v;
            case 'w': return w;
            case 'x': return x;
            default: return "Please Enter Correct sequence";
        }
    }
};

Solver::Solver()
{
    b = "RD' RU' R'U' RU R'F' RU R'U' R'FR DR'      ";
    c = "F RU' R'U' RU R'F' RU R'U' R'FR F'         ";
    d = "FU' R'U' RU R'F' RU R'U' R'FR2F'           ";
    e = "F'D RU' R'U' RU R'F' RU R'U' R'FR D'F      ";
    f = "F2D RU' R'U' RU R'F' RU R'U' R'FR D'F2     ";
    g = "RF RU' R'U' RU R'F' RU R'U' R'FR F'R'      ";
    h = "D RU' R'U' RU R'F' RU R'U' R'FR D'         ";
    i = "U' R'U' RU R'F' RU R'U' R'FR R             ";
    j = "R'U' R'U' RU R'F' RU R'U' R'FR R2          ";
    k = "R2U' R'U' RU R'F' RU R'U' R'F              ";
    l = "RU' R'U' RU R'F' RU R'U' R'FR              ";
    n = "D2 RF RU' R'U' RU R'F' RU R'U' R'FR F'R' D2";
    o = "D'RU' R'U' RU R'F' RU R'U' R'FR D          ";
    p = "R'F RU' R'U' RU R'F' RU R'U' R'FR F'R      ";
    r = "F2 RU' R'U' RU R'F' RU R'U' R'FR F2        ";
    s = "DR F RU' R'U' RU R'F' RU R'U' R'FR F' R'D' ";
    t = "D2 RU' R'U' RU R'F' RU R'U' R'FR D2        ";
    u = "F RU' R'U' RU R'F' RU R'U' R'FR F'         ";
    v = "D'F RU' R'U' RU R'F' RU R'U' R'FR F'D      ";
    w = "D2F RU' R'U' RU R'F' RU R'U' R'FR F'D2     ";
    x = "DF RU' R'U' RU R'F' RU R'U' R'FR F'D'      ";
}
int main()
{
    int i = 0;
    char seq[50];
    string solution;
    Solver sol;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"|            Cube Solver 2x2 v1.0             |"<<endl;
    cout<<"|            Developed by Pavan P             |"<<endl;
    cout<<"-----------------------------------------------"<<endl<<endl;
    cout<<"Enter the Sequence in small letters: ";
    cin.clear();
    cin>>seq;
    while(seq[i]!='\0')
    {
        i++;
    }
    cout<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"|    This may be a solution, try buddy        |"<<endl<<endl;
    for(int j=0;j<i;j++)
    {
        solution = sol.getSol(seq[j]);
        cout<<"| "<<solution<<" |"<<endl;
    }
    cout<<"-----------------------------------------------"<<endl;
    cout<<"Thank You"<<endl;
    cin.get();
        cin.get();
}

