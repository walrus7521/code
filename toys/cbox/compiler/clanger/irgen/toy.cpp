#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>

#include <string>
#include <vector>

using namespace llvm;

static LLVMContext Context;
static Module *module = new Module("my compiler", Context);

Function *createFunc(IRBuilder<> &Builder, std::string Name) {
    FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(), false);
    Function *fooFunc = llvm::Function::Create(funcType, 
            llvm::Function::ExternalLinkage, Name, module);
    return fooFunc;
}

int main(int argc, char const *argv[])
{
    static IRBuilder<> Builder(Context);
    Function *fooFunc = createFunc(Builder, "foo");
    verifyFunction(*fooFunc);
    module->print(llvm::errs(), nullptr);
    return 0;
}

