using System;

class TestMain
{
    public static void Main()
    {
        TurboEngine engine = new TurboEngine(30);
        Pickup van = new Pickup(engine);
        Console.WriteLine("engine: " + engine);
        Console.WriteLine("vehicle: " + van);
    }
}
