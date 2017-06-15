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

class Dispatch : public Base
{
private:
    int step = 0;
public:
    Dispatch()
    {
        //registerFn1( static_cast<GetNumStepsFn>(&DispatchGetNumSteps) );
        //registerFn2( static_cast<GetNextStepFn>(&DispatchGetNextStep) );
        //registerFn3( static_cast<ExecuteStepFn>(&DispatchExecuteStep) );
    }
    //int DispatchGetNumSteps(void *context) { GetNumStepsFn(nullptr); return 0; };
    //int DispatchGetNextStep(void *context) { return ++step; };
    //int DispatchExecuteStep(void *context, int step) { std::cout << "exec: " << step << std::endl; return 0; };
    void registerFn1( GetNumStepsFn fn ) {
        getNumSteps = fn;
    }
    void registerFn2( GetNextStepFn fn ) {
        getNextStep = fn;
    }
    void registerFn3( ExecuteStepFn fn ) {
        executeStep = fn;
    }
    GetNumStepsFn getNumSteps;
    GetNextStepFn getNextStep;
    ExecuteStepFn executeStep;

};

class DLL// : public Dispatch
{
private:
    int step = 0;
    Dispatch *disp;
public:
    DLL(Dispatch *d) : disp{d} {
        _d->registerFn1( static_cast<GetNumStepsFn>(&DispatchGetNumSteps) );
        _d->registerFn2( static_cast<GetNextStepFn>(&DispatchGetNextStep) );
        _d->registerFn3( static_cast<ExecuteStepFn>(&DispatchExecuteStep) );
    }
    int DispatchGetNumSteps(void *context) { return 5; };
    int DispatchGetNextStep(void *context) { return ++step; };
    int DispatchExecuteStep(void *context, int step) { std::cout << "exec: " << step << std::endl; return 0; };
};

int main()
{
    Dispatch *d = new Dispatch();
    DLL *dll = new DLL(d);
    int num_steps = d->getNumSteps(nullptr);
    //int next_step = 0;
    //for (int i = 0; i < num_steps; ++i) {
    //    d.DispatchExecuteStep(nullptr, next_step);
    //    next_step = d.DispatchGetNextStep(nullptr);
    //}
}
