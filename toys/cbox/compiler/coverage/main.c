
int fun1();
int fun2();
int fun4();

int fun1() { 
    int c = 3, x;
    if (c < 2) {
        x = c;
    } else {
        x = 0;
    }
    return fun2(); 
}

int fun2() { return 0;      }
int fun3() { return 42;     }


int main() { return fun1(); }

