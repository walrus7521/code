using System;

public interface IEngine
{
    int Size { get; }
    bool Turbo { get; }
}

public abstract class AbstractEngine : IEngine
{
    private int size;
    private bool turbo;

    public AbstractEngine(int size, bool turbo)
    {
        this.size = size;
        this.turbo = turbo;
    }

    public virtual int Size
    {
        get
        {
            return size;
        }
    }

    public virtual bool Turbo
    {
        get
        {
            return turbo;
        }
    }

    public override string ToString()
    {
        return this.GetType().Name + " (" + size + ")";
    }

}

public class StandardEngine : AbstractEngine
{
    public StandardEngine(int size) : base(size, false)
    {
        // not turbocharged
    }
}

public class TurboEngine : AbstractEngine
{
    public TurboEngine(int size) : base(size, true)
    {
        // turbocharged
    }
}
public interface IVehicle
{
    IEngine Engine { get; }
    VehicleColour Colour { get; }
    void Paint(VehicleColour colour);
    void CleanInterior();
    void CleanExteriorBody();
    void PolishWindows();
    void TakeForTestDrive();


}

public enum VehicleColour
{
    Unpainted, Blue, Black, Green,
    Red, Silver, White, Yellow
}

public abstract class AbstractVehicle : IVehicle
{
    private IEngine engine;
    private VehicleColour colour;

    public AbstractVehicle(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public AbstractVehicle(IEngine engine, VehicleColour colour)
    {
        this.engine = engine;
        this.colour = colour;
    }

    public virtual IEngine Engine
    {
        get
        {
            return engine;
        }
    }

    public virtual VehicleColour Colour
    {
        get
        {
            return colour;
        }
    }

    public virtual void Paint(VehicleColour colour)
    {
        this.colour = colour;
    }

    public virtual void CleanInterior()
    {
        Console.WriteLine("Cleaning interior...");
    }

    public virtual void CleanExteriorBody()
    {
        Console.WriteLine("Cleaning exterior body...");
    }

    public virtual void PolishWindows()
    {
        Console.WriteLine("Polish windows...");
    }

    public virtual void TakeForTestDrive()
    {
        Console.WriteLine("Taking for test drive...");
    }

    public override string ToString()
    {
        return this.GetType().Name + " (" + engine + ", " + colour + ")";
    }
}

public abstract class AbstractCar : AbstractVehicle
{
    public AbstractCar(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public AbstractCar(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public abstract class AbstractVan : AbstractVehicle
{
    public AbstractVan(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public AbstractVan(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public class Saloon : AbstractCar
{
    public Saloon(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public Saloon(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }   
}

public class Coupe : AbstractCar
{
    public Coupe(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public Coupe(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public class Sport : AbstractCar
{
    public Sport(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public Sport(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public class BoxVan : AbstractVan
{
    public BoxVan(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public BoxVan(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public class Pickup : AbstractVan
{
    public Pickup(IEngine engine)
        : this(engine, VehicleColour.Unpainted)
    {
    }

    public Pickup(IEngine engine, VehicleColour colour)
        : base(engine, colour)
    {
    }
}

public class Registration
{
    private IVehicle vehicle;

    public Registration(IVehicle vehicle)
    {
        this.vehicle = vehicle;
    }

    public virtual void AllocateLicensePlate()
    {
        Console.WriteLine("Allocating license plate...");
    }

    public virtual void AllocateVehicleNumber()
    {
        Console.WriteLine("Allocating vehicle number...");
    }
}

public class Documentation
{
    public static void PrintBrochure(IVehicle vehicle)
    {
        Console.WriteLine("Printing brochure...");
    }
}

public class VehicleFacade
{
    public virtual void PrepareForSale(IVehicle vehicle)
    {
        Registration reg = new Registration(vehicle);
        reg.AllocateVehicleNumber();
        reg.AllocateLicensePlate();

        Documentation.PrintBrochure(vehicle);

        vehicle.CleanInterior();
        vehicle.CleanExteriorBody();
        vehicle.PolishWindows();
        vehicle.TakeForTestDrive();
    }
}

public class Client
{
    static void Main()
    {
        // Create a blue saloon car... 
        IVehicle myCar = new Saloon(new StandardEngine(1300));
        myCar.Paint(VehicleColour.Blue);
        Console.WriteLine(myCar);

        // prepare the car for sale
        VehicleFacade fac = new VehicleFacade();
        fac.PrepareForSale(myCar);
    }
}
