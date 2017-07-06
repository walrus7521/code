using System;
using System.Windows.Forms;

// compile: msc /r:System.Windows.Forms.dll Calc.cs

namespace CalculatorExample
{
    class Program
    {
        static void Main()
        {
            Calc c = new Calc();
            int ans = c.Add(10, 84);
            Console.WriteLine("10 + 84 is {0}.", ans);
            Console.ReadLine();
            MessageBox.Show("Hello...");
        }
    }

    class Calc
    {
        public int Add(int x, int y)
        {
            return x + y;
        }
    }
}
