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
public interface IVehicle : ICloneable
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

    public virtual object Clone()
    {
        return this.MemberwiseClone();
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


public class VehicleManagerLazy
{
    // these are the prototypes from which all will be carved
    // we lazy allocate them as-needed.
    private IVehicle saloon, coupe, sport, boxVan, pickup;

    public VehicleManagerLazy()
    {
    }

    public virtual IVehicle CreateSaloon()
    {
        if (saloon == null)
        {
            saloon = new Saloon(new StandardEngine(1300));
        }
        return (IVehicle) saloon.Clone();
    }

    public virtual IVehicle CreateCoupe()
    {
        if (coupe == null)
        {
            coupe  = new Coupe(new StandardEngine(1300));
        }
        return (IVehicle) coupe.Clone();
    }

    public virtual IVehicle CreateSport()
    {
        if (sport == null)
        {
            sport  = new Sport(new StandardEngine(1300));
        }
        return (IVehicle) sport.Clone();
    }

    public virtual IVehicle CreateBoxVan()
    {
        if (boxVan == null)
        {
            boxVan = new BoxVan(new StandardEngine(1300));
        }
        return (IVehicle) boxVan.Clone();
    }

    public virtual IVehicle CreatePickup()
    {
        if (pickup == null)
        {
            pickup = new Pickup(new StandardEngine(1300));
        }
        return (IVehicle) pickup.Clone();
    }

}





