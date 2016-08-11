#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdio>

using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "n and p should be non-negative.";
  }
} myex;

struct Calculator
{
    int power(int n, int p) { 
        if ((n < 0) || (p < 0)) {
            throw runtime_error("n and p should be non-negative");
        }
        if (p == 0) return 1;
        int prod = n;
        for (int i = 1; i < p; ++i) {
            prod *= n;
        }
        return prod; 
    }

};


int main()
{
    Calculator myCalculator=Calculator();
    int T,n,p;

    //n = 3, p = 5;
    //cout << myCalculator.power(n,p) << endl;
    //return 0;

    cin>>T;
    while(T-->0){
      if(scanf("%d %d",&n,&p)==2){
         try{
               int ans=myCalculator.power(n,p);
               cout<<ans<<endl; 
         }
         catch(exception& e){
             cout<<e.what()<<endl;
         }
      }
    }
    
}
