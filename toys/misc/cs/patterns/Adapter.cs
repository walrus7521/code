using System;
using System.Collections;
using System.Collections.Generic;

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

// bogus implementation to make this work
// this would normally be provided by a 3rd party.
public class SuperGreenEngine
{
    public SuperGreenEngine(int engineSize)
    {
        EngineSize = engineSize;
    }
    public int EngineSize;
    public string ToStringerize()
    {
        return this.GetType().Name + " GREENAGE (" + EngineSize + ")";
    }
}

// 3 steps to adapt a class
//   1. Extend the class we are adapting to
//   2. Specify the class we are adapting from in the ctor and store
//      a reference to it in an instance variable.
//   3. For each method in the class you are extending, override it
//      to delegate to the corresponding method of the class you are
//      adapting from.

// we are adapting FROM SuperGreenEngine
// we are adapting TO AbstractEngine
// note that SuperGreenEngine has adapted the ToString() method
// from the AbstractEngine rather than that of SuperGreenEngine.
public class SuperGreenEngineAdapter : AbstractEngine
{
    private SuperGreenEngine greenEngine; // class adapting from

    public SuperGreenEngineAdapter(SuperGreenEngine greenEngine)
        : base(greenEngine.EngineSize, false) // pass to superclass ctor
    {
        this.greenEngine = greenEngine;
    }

    // overridden method from TO class
    // as a delegate for the FROM class
    public override string ToString() //method in TO class (AbstractEngine)
    {
        return greenEngine.ToStringerize(); // method in FROM class
    }
}

// mcs ClientAdapter.cs AbstractFactory2.cs Adapter.cs

namespace MyClient
{
    public class Client
    {
        public static void Main()
        {
            IList<IEngine> engines = new List<IEngine>();

            engines.Add(new StandardEngine(1300));
            engines.Add(new StandardEngine(1600));
            engines.Add(new TurboEngine(2000));

            // Adapt the new engine type
            SuperGreenEngine greenEngine = new SuperGreenEngine(1200);
            engines.Add(new SuperGreenEngineAdapter(greenEngine));

            foreach (var engine in engines)
            {
                Console.WriteLine(engine);
            }
            Console.Read();
        }
    }
}
