using System;

public class Logger
{
    // Field
    private string name;

    // Constructor that takes no arguments.
    public Logger()
    {
        name = "unknown";
        Console.WriteLine("Logger() name: " + name);
    }

    // Constructor that takes one argument.
    public Logger(string nm)
    {
        name = nm;
        Console.WriteLine("Logger(name): " + name);
     }

    // Method
    public void SetName(string newName)
    {
        name = newName;
        Console.WriteLine ("SetName: " + name);
    }
}

class TestLogger
{
    static void Main() {
        var log = new Logger("dude");
        log.SetName("sup");
    }
}
