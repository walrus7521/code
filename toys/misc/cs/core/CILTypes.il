.assembly extern mscorlib
{
    .publickeytoken = (B7 7A 5C 56 19 34 E0 89)
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
    .class public sealed enum MyEnum 
    {
        .field public static literal valuetype MyNamespace.MyEnum A = int32(0)
        .field public static literal valuetype MyNamespace.MyEnum B = int32(1)
        .field public static literal valuetype MyNamespace.MyEnum C = int32(2)
    }

    .class public MyBaseClass 
    {
        .field private string stringField = "hello!"
        .field private int32 intField = int32(42)
        // constructor
        .method public hidebysig specialname rtspecialname
          instance void .ctor(string s, int32 i) cil managed
        {
            ret
        }
        // new method - getter
        .method public hidebysig specialname
          instance string get_TheString() cil managed
        {
            .maxstack 1
            //ldstr MyNamespace.MyBaseClass.stringField
            ret
        }
        // new method - setter
        .method public hidebysig specialname
          instance void set_TheString(string 'value') cil managed
        {
        }

        // add property - maps to pair of methods w/ get_/set_ prefixes
        .property instance string TheString()
        {
            .get instance string
              MyNamespace.MyBaseClass::get_TheString()
            .set instance void
              MyNamespace.MyBaseClass::set_TheString(string)
        }

        .method public hidebysig static void MyMethod(int32 inputInt,
                int32& refInt,
                class [mscorlib]System.Collections.ArrayList ar,
                [out] int32& outputInt) cil managed
        {
        }

        .method public hidebysig static void
          MyLocalVariables() cil managed
        {
            .maxstack 8
            // define 3 locals
            .locals init([0] string myStr, [1] int32 myInt, [2] object myObj)
            // load a string onto the stack
            ldstr "CIL is fun!"
            // pop off current value and store in local [0]
            stloc.0

            // load const of type i4 set to value 33
            ldc.i4 33
            // pop off current value and store in local [1]
            stloc.1

            // create new obj on stack
            newobj instance void [mscorlib]System.Object::.ctor()
            // pop off value and store in local [2]
            stloc.2
            ret
        }

        .method public hidebysig static int32 Add(int32 a, int32 b) cil managed
        {
            .maxstack 2
            ldarg.0
            ldarg.1
            add
            ret
        }
    } 
    .class public MyDerivedClass
        extends MyNamespace.MyBaseClass {}

    // List<int> myInts = new List<int>();
    //newobj instance void class [mscorlib]System.Collections.Generic.List`1<int32>::.ctor()
    // Dictionary<string, int> d = new Dictionary<string, int>();
    //newobj instance void .class [mscorlib]
    //    System.Collections.Generic.Dictionary`2<string, int32>::.ctor()
    // List<List<int>> myInts = new List<List<int>>();
    //newobj instance void .class [mscorlib]
    //    System.Collections.Generic.List`1<class
    //     [mscorlib]System.Collections.Generic.List`1<int32>>::ctor()

}

