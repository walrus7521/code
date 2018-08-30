using System;

// mcs Singleton.cs
public class SerialNumberGenerator
{
    // static members
    private static volatile SerialNumberGenerator instance;
    private static object synchronizationRoot = new Object();

    public static SerialNumberGenerator Instance {
        get {
            if (instance == null) {
                lock (synchronizationRoot) {
                    if (instance == null) {
                        instance = new SerialNumberGenerator();
                    }
                }
            }
            return instance;
        }
    }
    // instance variables
    private int count;
    // private constructor
    private SerialNumberGenerator() {
    }
    // instance methods
    public virtual int NextSerial {
        get {
            return ++count;
        }
    }
}

public class Tester
{
    public static void Main()
    {
        var sngen = SerialNumberGenerator.Instance;
        for (int i = 0; i < 4; ++i) {
            int sn = sngen.NextSerial;
            Console.WriteLine("serial number: " + sn);
        }
    }
}


