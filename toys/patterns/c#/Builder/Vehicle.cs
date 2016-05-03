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








