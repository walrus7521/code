using System;

class Car
{
    public string PetName {get;set;}
    public string Color {get;set;}
    public int Speed {get;set;}
    public string Make {get;set;}
}

public class Client
{

    static void GetGCInfo()
    {
        Console.WriteLine("Estimated bytes on the heap: {0}", GC.GetTotalMemory(false));
        Console.WriteLine("This OS has {0} object generations", GC.MaxGeneration+1);

        Car refToMyCar = new Car();
        Console.WriteLine(refToMyCar.ToString());
        Console.WriteLine("Generation of refToMyCar is: {0}", 
                GC.GetGeneration(refToMyCar));

        GC.Collect(0);
        GC.WaitForPendingFinalizers();
        Console.WriteLine("Generation of refToMyCar is: {0}", 
                GC.GetGeneration(refToMyCar));
    }

    static void Main()
    {
        GetGCInfo();
    }

}
