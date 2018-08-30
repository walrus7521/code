using System;

public interface IEngine
{
    int Size { get; }
    bool Turbo { get; }

    void Start();
    void Stop();
    void IncreasePower();
    void DecreasePower();
}

public abstract class AbstractEngine : IEngine
{
    private int size;
    private bool turbo;
    private bool running;
    private int power;

    public AbstractEngine(int size, bool turbo)
    {
        this.size = size;
        this.turbo = turbo;
        running = false;
        power = 0;
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

    public virtual void Start()
    {
        running = true;
    }

    public virtual void Stop()
    {
        running = false;
        power = 0;
    }

    public virtual void IncreasePower()
    {
        if ((running) && (power < 10))
        {
            power++;
        }
    }

    public virtual void DecreasePower()
    {
        if ((running) && (power > 0))
        {
            power--;
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

public abstract class AbstractDriverControls
{
    private IEngine engine;

    public AbstractDriverControls(IEngine engine)
    {
        this.engine = engine;
    }

    public virtual void IgnitionOn()
    {
        Console.WriteLine("IgnitionOn");
        engine.Start();
    }

    public virtual void IgnitionOff()
    {
        Console.WriteLine("IgnitionOff");
        engine.Stop();
    }

    public virtual void Accelerate()
    {
        Console.WriteLine("Accelerate");
        engine.IncreasePower();
    }

    public virtual void Brake()
    {
        Console.WriteLine("Brake");
        engine.DecreasePower();
    }
}


public class StandardControls : AbstractDriverControls
{
    public StandardControls(IEngine engine) : base(engine) {
    }
    // no extra functions
}

public class SportControls : AbstractDriverControls
{
    public SportControls(IEngine engine) : base(engine) {
    }

    public virtual void AccelerateHard()
    {
        Accelerate();
        Accelerate();
    }
}

class Client
{
    public static void Main()
    {
        IEngine engine = new StandardEngine(1300);
        StandardControls controls1 = new StandardControls(engine);
        controls1.IgnitionOn();
        controls1.Accelerate();
        controls1.Brake();
        controls1.IgnitionOff();

        // now use sporty
        SportControls controls2 = new SportControls(engine);
        controls2.IgnitionOn();
        controls2.Accelerate();
        controls2.AccelerateHard();
        controls2.Brake();
        controls2.IgnitionOff();

    }


}

