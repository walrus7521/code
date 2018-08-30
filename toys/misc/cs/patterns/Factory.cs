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

public abstract class VehicleFactory
{
    public enum DrivingStyle
    {
        Economical, Midrange, Powerful
    }
    public enum Category
    {
        Car, Van
    }
    public virtual IVehicle Build(DrivingStyle style,
                                  VehicleColour colour)
    {
        IVehicle v = SelectVehicle(style);
        v.Paint(colour);
        return v;
    }
    // This is the "factory methoc"
    protected internal abstract IVehicle SelectVehicle(
                                   DrivingStyle style);


    public static IVehicle Make(Category cat,
                                DrivingStyle style,
                                VehicleColour colour)
    {
        VehicleFactory factory;
        if (cat == Category.Car)
        {
            factory = new CarFactory();
        }
        else
        {
            factory = new VanFactory();
        }
        return factory.Build(style, colour);
    }
}

public class CarFactory : VehicleFactory
{
    protected internal override IVehicle SelectVehicle(
                                   DrivingStyle style)
    {
        if (style == DrivingStyle.Economical)
        {
            return new Saloon(new StandardEngine(1300));
        } else
        if (style == DrivingStyle.Midrange)
        {
            return new Coupe(new StandardEngine(1600));
        } else
        {
            return new Sport(new TurboEngine(2000));
        }
    }
}

public class VanFactory : VehicleFactory
{
    protected internal override IVehicle SelectVehicle(
                                   DrivingStyle style)
    {
        if ((style == DrivingStyle.Economical) ||
            (style == DrivingStyle.Midrange))
        {
            return new Pickup(new StandardEngine(2200));
        } else
        {
            return new BoxVan(new TurboEngine(2500));
        }
    }
}

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

