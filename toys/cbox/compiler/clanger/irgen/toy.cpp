#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

using namespace llvm;

//static LLVMContext &Context = getGlobalContext();
static LLVMContext Context;
static Module *module = new Module("my compiler", Context);

int main(int argc, char const *argv[])
{
    //module->dump(); // broken!!
    module->print(llvm::errs(), nullptr);
    return 0;
}

