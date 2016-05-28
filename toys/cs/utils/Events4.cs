using System;

public class CarEventArgs : EventArgs
{
    public readonly string msg;
    public CarEventArgs(string msg)
    {
        this.msg = msg;
    }
}

public class Car
{
    public int CurrentSpeed {get;set;}
    public int MaxSpeed {get;set;}
    public string PetName {get;set;}
    private bool carIsDead;
    public Car() { MaxSpeed = 100; }
    public Car(string name, int maxSp, int currSp)
    {
        CurrentSpeed = currSp;
        MaxSpeed = maxSp;
        PetName = name;
    }
    // define a delegate type
    public delegate void CarEngineHandler(object sender, CarEventArgs e);
    // these are the events
    public event CarEngineHandler Exploded;
    public event CarEngineHandler AboutToBlow;

    // can also do Generic Events
    //public event CarEngineHandler<CarEventArgs> Vaporized;

    public void Accelerate(int delta)
    {
        if (carIsDead) {
            if (Exploded != null) {
                Exploded(this, new CarEventArgs("Sorry, this car is dead..."));
            }
        } else {
            CurrentSpeed += delta;
            if (10 == (MaxSpeed - CurrentSpeed)
                    && AboutToBlow != null) {
                AboutToBlow(this, new CarEventArgs("Careful buddy! Gonna blow!"));
            }
            if (CurrentSpeed >= MaxSpeed) {
                carIsDead = true;
            } else {
                Console.WriteLine("CurrentSpeed = {0}", CurrentSpeed);
            }
        }
    }
    public override string ToString()
    {
        return string.Format("Car->{0}", PetName);
    }
}

class client
{
    public static void Boom(object sender, CarEventArgs e)
    {
        Console.WriteLine("Boom: {0} = {1}", sender, e.msg);
        if (sender is Car) {
            Car c = (Car) sender;
            Console.WriteLine(".....dude your car died because you were going {0} MPH", c.CurrentSpeed);
        }
    }
    public static void CloseCall(object sender, CarEventArgs e)
    {
        Console.WriteLine("CloseCall: {0} = {1}", sender, e.msg);
        if (sender is Car) {
            Car c = (Car) sender;
            Console.WriteLine(".....your current car speed is: {0}", c.CurrentSpeed);
        }
    }
    public static void Main()
    {
        int blowCount = 0;
        string dude = "wusup homi";
        Car c = new Car("Lois", 100, 50);
        c.Exploded += Boom;
        c.AboutToBlow += CloseCall;

        // anonymous method
        c.AboutToBlow += delegate
        {
            blowCount++;
            // can access locals of method defining this anonymous delegate
            // they are outer variables
            Console.WriteLine("Eke! {0} you are going to fast!!!", dude);
        };

        c.Exploded += delegate(object sender, CarEventArgs e)
        {
            blowCount++;
            Console.WriteLine("Boom boom boom: {0} = {1}", sender, e.msg);
            if (sender is Car) {
                Car car = (Car) sender;
                Console.WriteLine(".....call the coroner {0}", car.CurrentSpeed);
            }
        };

        c.Accelerate(20);
        c.Accelerate(20);
        c.Accelerate(20);
        c.Accelerate(20);

        Console.WriteLine("blow count: {0}", blowCount);
    }
}
