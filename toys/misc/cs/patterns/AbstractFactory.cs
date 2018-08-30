using System;

public interface IBody
{
    string BodyParts { get; }
    void Draw();
}

public class CarBody : IBody
{
    public virtual string BodyParts
    {
        get 
        {
            return "Body shell parts for a car.";
        }
    }
    public void Draw()
    {
        Console.WriteLine("Drawing Carbody...");
    }
}

public class VanBody : IBody
{
    public virtual string BodyParts
    {
        get
        {
            return "Body shell parts for a van.";
        }
    }
    public void Draw()
    {
        Console.WriteLine("Drawing Carbody...");
    }
}

public interface IChassis
{
    string ChassisParts { get; }
}

public class CarChassis : IChassis
{
    public virtual string ChassisParts
    {
        get
        {
            return "Chassis parts for a car.";
        }
    }
}

public class VanChassis : IChassis
{
    public virtual string ChassisParts
    {
        get
        {
            return "Chassis parts for a van.";
        }
    }
}

public interface IGlassware
{
    string GlasswareParts { get; }
}

public class CarGlassware : IGlassware
{
    public virtual string GlasswareParts
    {
        get
        {
            return "Window glassware for a car.";
        }
    }
}

public class VanGlassware : IGlassware
{
    public virtual string GlasswareParts
    {
        get
        {
            return "Window glassware for a van.";
        }
    }
}

// concrete class, usually implemented as a singleton
public abstract class AbstractVehicleFactory
{
    public abstract IBody CreateBody();
    public abstract IChassis CreateChassis();
    public abstract IGlassware CreateGlassware();
}

public class CarFactory : AbstractVehicleFactory
{
    public override IBody CreateBody()
    {
        return new CarBody();
    }

    public override IChassis CreateChassis()
    {
        return new CarChassis();
    }

    public override IGlassware CreateGlassware()
    {
        return new CarGlassware();
    }
}

public class VanFactory : AbstractVehicleFactory
{
    public override IBody CreateBody()
    {
        return new VanBody();
    }

    public override IChassis CreateChassis()
    {
        return new VanChassis();
    }

    public override IGlassware CreateGlassware()
    {
        return new VanGlassware();
    }
}

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
