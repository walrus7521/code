using System;
using System.Collections;
using System.Collections.Generic;


// use List<T> FindAll(Predicate<T> match);
// Predicate<T> is a function that takes type T and returns bool
// public delegate bool Predicate<T>(T obj);
// calls to FindAll result in each item in the list being passed to Predicate.

class Program
{
    static bool IsEvenNumber(int i)
    {
        return (i % 2) == 0;
    }

    static void TraditionalDelegateSyntax()
    {
        List<int> list = new List<int>();
        list.AddRange(new int[] {20, 1, 4, 8, 9, 44});
        // call FindAll using traditional delegate syntax
        Predicate<int> callback = new Predicate<int>(IsEvenNumber);
        List<int> evenNumbers = list.FindAll(callback);
        Console.WriteLine("here are your even numbers");
        foreach (int e in evenNumbers) {
            Console.Write("{0}\t", e);
        }
        Console.WriteLine();
    }

    static void AnonymousSyntax()
    {
        List<int> list = new List<int>();
        list.AddRange(new int[] {20, 1, 4, 8, 9, 44});
        List<int> evenNumbers = list.FindAll(delegate(int i)
                { return (i % 2) == 0; } );
        Console.WriteLine("here are your even numbers");
        foreach (int e in evenNumbers) {
            Console.Write("{0}\t", e);
        }
        Console.WriteLine();
    }

    static void LambdaExpressionSyntax()
    {
        List<int> list = new List<int>();
        list.AddRange(new int[] {20, 1, 4, 8, 9, 44});
        List<int> evenNumbers1 = list.FindAll(i => (i % 2) == 0);
        List<int> evenNumbers2 = list.FindAll((int i) => (i % 2) == 0);
        List<int> evenNumbers3 = list.FindAll((int i) => ((i % 2) == 0));
        List<int> evenNumbers4 = list.FindAll((i) => 
        {
            Console.WriteLine("value of i is currently: {0}", i);
            bool isEven = ((i % 2) == 0);
            return isEven;
        });
        Console.WriteLine("here are your even numbers");
        foreach (int e in evenNumbers4) {
            Console.Write("{0}\t", e);
        }
        Console.WriteLine();
    }

    public class SimpleMath
    {
        public delegate void MathMessage(string msg, int result);
        public delegate string ZeroMessage();
        private MathMessage mmDelegate;
        public ZeroMessage zzDelegate;

        public void SetMathHandler(MathMessage target)
        {
            mmDelegate += target;
        }
        public void Add(int x, int y)
        {
            if (mmDelegate != null) {
                mmDelegate.Invoke("adding has completed", x+y);
            }
            if (zzDelegate != null) {
                zzDelegate.Invoke();
            }
        }
    }

    static void LambdaExpressionsMultipleParams()
    {
        SimpleMath m = new SimpleMath();
        // register with delegate as lambda expression
        m.SetMathHandler((msg, result) =>
        {
            Console.WriteLine("Message: {0}, Result: {1}", msg, result);
        });
        m.zzDelegate += () => { Console.WriteLine("sup homes"); return "sup"; };
        // this will trigger the lambda expressions
        m.Add(10, 10);
    }

    static void Main()
    {
        //TraditionalDelegateSyntax();
        //AnonymousSyntax();
        //LambdaExpressionSyntax();
        LambdaExpressionsMultipleParams();
        return;


        //
        // Use implicitly typed lambda expression.
        // ... Assign it to a Func instance.
        //
        Func<int, int> func1 = x => x + 1;
        //
        // Use lambda expression with statement body.
        //
        Func<int, int> func2 = x => { return x + 1; };
        //
        // Use formal parameters with expression body.
        //
        Func<int, int> func3 = (int x) => x + 1;
        //
        // Use parameters with a statement body.
        //
        Func<int, int> func4 = (int x) => { return x + 1; };
        //
        // Use multiple parameters.
        //
        Func<int, int, int> func5 = (x, y) => x * y;
        //
        // Use no parameters in a lambda expression.
        //
        Action func6 = () => Console.WriteLine("yo");
        //
        // Use delegate method expression.
        //
        Func<int, int> func7 = delegate(int x) { return x + 1; };
        //
        // Use delegate expression with no parameter list.
        //
        Func<int> func8 = delegate { return 1 + 1; };
        //
        //
        //
        // Invoke each of the lambda expressions and delegates we created.
        //
        // ... The methods above are executed.
        //
        Console.WriteLine(func1.Invoke(1));
        Console.WriteLine(func2.Invoke(1));
        Console.WriteLine(func3.Invoke(1));
        Console.WriteLine(func4.Invoke(1));
        Console.WriteLine(func5.Invoke(2, 2));
        func6.Invoke();
        Console.WriteLine(func7.Invoke(1));
        Console.WriteLine(func8.Invoke());
    }
}
