#include <iostream>
#include <memory>
#include <functional>

class Base
{
public:
    typedef int (Base::*GetNumStepsFn)( void* );
    typedef int (Base::*GetNextStepFn)( void* );
    typedef int (Base::*ExecuteStepFn)( void*, int );

    virtual void registerFn1( GetNumStepsFn fn ) = 0;
    virtual void registerFn2( GetNextStepFn fn ) = 0;
    virtual void registerFn3( ExecuteStepFn fn ) = 0;
};

class DLL;

class Dispatch : public Base
{
private:
    int step = 0;
public:
    int dude = 42;
    Dispatch() {}

    void registerDLL( DLL *dll);

    void registerFn1( GetNumStepsFn fn ) {
        getNumSteps = fn;
    }
    void registerFn2( GetNextStepFn fn ) {
        getNextStep = fn;
    }
    void registerFn3( ExecuteStepFn fn ) {
        executeStep = fn;
    }

    Base::GetNumStepsFn getNumSteps;
    Base::GetNextStepFn getNextStep;
    Base::ExecuteStepFn executeStep;
};

class DLL : public Dispatch
{
private:
    int step = 0;
    Dispatch *disp;
public:
    DLL() {}
    int DispatchGetNumSteps(void *context) { return 5; }
    int DispatchGetNextStep(void *context) { return ++step; }
    int DispatchExecuteStep(void *context, int step) { 
        std::cout << "exec: " << 
        step << std::endl; return 0; 
    }
};

void Dispatch::registerDLL( DLL *dll ) {
    getNumSteps = static_cast<Base::GetNumStepsFn>(&DLL::DispatchGetNumSteps);
    getNextStep = static_cast<Base::GetNextStepFn>(&DLL::DispatchGetNextStep);
    executeStep = static_cast<Base::ExecuteStepFn>(&DLL::DispatchExecuteStep);
}

using namespace std;

int main()
{
    Dispatch *d = new Dispatch();
    DLL *dll = new DLL();
    d->registerDLL(dll);
    int num_steps = d->dude; //getNumSteps(nullptr);
    //auto steps = d->getNumSteps(nullptr);
    //steps(nullptr);
    cout << "num steps: " << num_steps << endl;
    //int next_step = 0;
    //for (int i = 0; i < num_steps; ++i) {
    //    d.DispatchExecuteStep(nullptr, next_step);
    //    next_step = d.DispatchGetNextStep(nullptr);
    //}
}
