using System;
using System.Dynamic;

// https://www.simple-talk.com/dotnet/.net-framework/dynamic-language-integration-in-a-c-world/
// csc /target:library calc.cs
// csc calc.cs

public class Calculator 
{
    public double add(double argA, double argB)
    {
        return argA + argB;
    }
    public double sub(double argA, double argB)
    {
        return argA - argB;
    }
}

namespace DynamicCS
{
    public class DynamicCalc: DynamicObject
    {
        public Calculator calc;
        public DynamicCalc()
        {
            calc = new Calculator();
        }
        public double add(double argA, double argB)
        {
            return calc.add(argA, argB);
        }
        public double sub(double argA, double argB)
        {
            return calc.sub(argA, argB);
        }

        public override bool TryGetMember(GetMemberBinder binder, out object          result)
        {
            result = null;
            switch (binder.Name)
            {
                case "add":
                result = (Func<double, double ,double>) ((double a, double b)
                       => calc.add(a, b));
                    return true;
                case "sub":
                result = (Func<double, double, double>) ((double a, double b)
                       => calc.sub(a, b));
                    return true;
            }
            return false;
        }
    }
}

//namespace XCli
//{
//    using DynamicCS;
    public class Client
    {
//
        public static void Main()
        {
//            DynamicCS.DynamicCalc calc = new DynamicCS.DynamicCalc();
//            var x = calc.calc.add(3.0, 4.0);
//            Console.WriteLine("x = " + x );
//            
        }
    }
//}

