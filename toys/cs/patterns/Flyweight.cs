using System;
using System.Collections.Generic;
using System.Threading;

public interface IEngine
{
    // Properties having intrinsic (i.e. shared) state
    int Size { get; }
    bool Turbo { get; }

    // Methods having extrinsic (i.e. unshared) state
    void Diagnose(IDiagnosticTool tool);

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

    public virtual void Diagnose(IDiagnosticTool tool)
    {
        tool.RunDiagnosis(this);
    }

    public override string ToString()
    {
        return this.GetType().Name + " (" + size + ")";
    }

    //public override int GetHashCode()
    //{
    //    int result = size.GetHashCode() + turbo.GetHashCode();
    //    return result;
    //}
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

public interface IDiagnosticTool
{
    void RunDiagnosis(object obj);
}

public class EngineDiagnosticTool : IDiagnosticTool
{
    public virtual void RunDiagnosis(object obj)
    {
        Console.WriteLine("Starting engine diagnostic tool for " + obj);
        Thread.Sleep(5000);
        Console.WriteLine("Engine diagnosis complete");
    }
}

public class EngineFlyweightFactory {
    private IDictionary<int?, IEngine> standardEnginePool;
    private IDictionary<int?, IEngine> turboEnginePool;
    public EngineFlyweightFactory()
    {
        standardEnginePool = new Dictionary<int?, IEngine>();
        turboEnginePool = new Dictionary<int?, IEngine>();
    }
    public virtual IEngine GetStandardEngine(int size)
    {
        IEngine e = null;
        bool found = standardEnginePool.TryGetValue(size, out e);
        if (! found)
        {
            e = new StandardEngine(size);
            standardEnginePool[size] = e;
        }
        return e;
    }
    public virtual IEngine GetTurboEngine(int size)
    {
        IEngine e = null;
        bool found = turboEnginePool.TryGetValue(size, out e);
        if (!found)
        {
            e = new TurboEngine(size);
            turboEnginePool[size] = e;
        }
        return e;
    }
}

class Client
{
    public static void Main()
    {

        // Create the flyweight factory... 
        EngineFlyweightFactory factory = new EngineFlyweightFactory();
        // Create the diagnostic tool
        IDiagnosticTool tool = new EngineDiagnosticTool();
        // Get the flyweights and run diagnostics on them
        IEngine standard1 = factory.GetStandardEngine(1300);
        standard1.Diagnose(tool);
        IEngine standard2 = factory.GetStandardEngine(1300);
        standard2.Diagnose(tool);
        IEngine standard3 = factory.GetStandardEngine(1300); 
        standard3.Diagnose(tool); 
        IEngine standard4 = factory.GetStandardEngine(1600); 
        standard4.Diagnose(tool); 
        IEngine standard5 = factory.GetStandardEngine(1600); 
        standard5.Diagnose(tool);

        // Show that objects are shared 
        Console.WriteLine(standard1.GetHashCode()); 
        Console.WriteLine(standard2.GetHashCode()); 
        Console.WriteLine(standard3.GetHashCode()); 
        Console.WriteLine(standard4.GetHashCode()); 
        Console.WriteLine(standard5.GetHashCode());
    }
}


