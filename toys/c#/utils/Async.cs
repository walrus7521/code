using System;
using System.IO;
using System.Threading;

delegate int SomeDelegate(int x);
delegate string SomeDelegate2();

class Program
{
    static void Main(string[] args)
    {
        SomeDelegate sd = SquareNumber;
        SomeDelegate2 sd2 = Cube;
        Console.WriteLine("Before invoke.");
        IAsyncResult asyncRes = sd.BeginInvoke(10, null, null);
        IAsyncResult asyncRes2 = sd2.BeginInvoke(null, null);
        Console.WriteLine("After invoke.");
        int res = sd.EndInvoke(asyncRes);
        string res2 = sd2.EndInvoke(asyncRes2);
        Console.WriteLine(res);
        Console.WriteLine(res2);
        Console.ReadLine();
    }

    static int SquareNumber(int a)
    {
        Console.WriteLine("SquareNumber invoked ...");
        Thread.Sleep(1000);
        return a*a;
    }

    static string Cube()
    {
        Console.WriteLine("Cube invoked ...");
        Thread.Sleep(1000);
        string s = "sup";
        return s;
    }
    
}
