using System;

// mcs ClientPrototype.cs Prototype.cs

namespace MyClient
{
    public class Client
    {
        public static void Main()
        {
            VehicleManagerLazy manager = new VehicleManagerLazy();

            IVehicle saloon1 = manager.CreateSaloon();
            IVehicle saloon2 = manager.CreateSaloon();
            IVehicle pickup1 = manager.CreatePickup();

            Console.WriteLine(saloon1);
            Console.WriteLine(saloon2);
            Console.WriteLine(pickup1);

            Console.Read();
        }
    }
}
