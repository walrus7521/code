using System;

// mcs ClientFactory.cs Factory.cs AbstractFactory2.cs

namespace MyClient
{
    public class Client
    {
        public static void Main()
        {
            // I want an economical car, coloured blue
            VehicleFactory carFactory = new CarFactory();
            IVehicle car = carFactory.Build(
                                VehicleFactory.DrivingStyle.Economical,
                                VehicleColour.Blue);
            Console.WriteLine(car);

            // I want a "white van"
            VehicleFactory vanFactory = new VanFactory();
            IVehicle van = vanFactory.Build(
                                VehicleFactory.DrivingStyle.Powerful,
                                VehicleColour.White);
            Console.WriteLine(van);

            // use the static Make method to create a red sports car
            IVehicle sporty = VehicleFactory.Make(
                                VehicleFactory.Category.Car,
                                VehicleFactory.DrivingStyle.Powerful,
                                VehicleColour.Red);
            Console.WriteLine(sporty);

        }
    }
}
