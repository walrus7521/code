calc: lex.yy.c calc.tab.c calc.h calcer.cpp main.cpp
	g++ -std=c++14 -DLLVM -I/usr/local/opt/llvm/include calcer.cpp main.cpp lex.yy.c calc.tab.c -fno-rtti -L/usr/local/opt/llvm/lib -lLLVMCore -lLLVMSupport -lLLVMTableGen -lLLVMDemangle -lcurses -o calc

lex.yy.c:
	flex calc.l

calc.tab.c:
	bison -d calc.y

clean:
	rm -rf lex.yy.c calc.tab.c calc.tab.h calc
