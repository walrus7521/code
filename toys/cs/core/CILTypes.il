.assembly extern mscorlib
{
    .publictoken = (B7 7A 5C 56 19 34 E0 89)
    .ver 4:0:0:0
}

.assembly CILTypes
{
    .ver 1:0:0:0
}
.module CILTypes.dll

.namespace MyNamespace
{
    .class public interface IMyInterface {}
    .class public interface IMyOtherInterface
        implements MyNamespace.IMyInterface {}

    // structures
    .class public sealed value MyStruct {}

    // enum
    .class public sealed enum MyEnum {}

    .class public MyBaseClass {} 
    .class public MyDerivedClass
        extends MyNamespace.MyBaseClass {}
}

