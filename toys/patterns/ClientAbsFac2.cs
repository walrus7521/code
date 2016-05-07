using System;

// mcs ClientAbsFac2.cs AbstractFactory2.cs

namespace MyClient
{
    public class Client
    {
        static void Main()
        {
            TurboEngine engine = new TurboEngine(30);
            Pickup van = new Pickup(engine);
            Console.WriteLine("engine: " + engine);
            Console.WriteLine("vehicle: " + van);
        }
    }
}
