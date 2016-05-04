using System;

// mcs ClientAbsFac.cs AbstractFactory.cs

namespace MyClient
{
    public class Client
    {
        public static void Main()
        {
            // specify the platform here: "mac", "windows", "android"
            string whatToMake = "car"; // "van"
        
            AbstractVehicleFactory factory = null;

            // Create the correct 'factory'...
            if (whatToMake.Equals("car"))
            {
                factory = new CarFactory();
            }
            else
            {
                factory = new VanFactory();
            }

            // Create the vehicle's component parts ...
            // These will either be all car parts or all van parts
            // These can be widgets of different platforms - Mac, Windows, Android
            IBody vehicleBody = factory.CreateBody();
            IChassis vehicleChassis = factory.CreateChassis();
            IGlassware vehicleGlassware = factory.CreateGlassware();

            // Show what we've created...
            Console.WriteLine(vehicleBody.BodyParts);
            Console.WriteLine(vehicleChassis.ChassisParts);
            Console.WriteLine(vehicleGlassware.GlasswareParts);

            vehicleBody.Draw();
        }
    }
}
