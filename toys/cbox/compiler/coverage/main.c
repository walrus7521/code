
int fun1();
int fun2();
int fun3();
int fun4();

int fun1() { return fun2(); }
int fun2() { return fun3(); }
int fun3() { return 42;     }


int main() { return fun1(); }

