using System;
using System.Collections.Generic;
using System.Threading;

public class Test
{
    static void Main()
    {
        var threads = new List<Thread>();
        for (int i = 0; i < 10; i++)
        {
            int copy = i;
            Thread thread = new Thread(() => DoWork(copy));
            thread.Start();
            threads.Add(thread);
        }

        Console.WriteLine("Main thread blocking");
        foreach (Thread thread in threads)
        {
            thread.Join();
        }
        Console.WriteLine("Main thread finished");
    }

    static void DoWork(int thread)
    {
        Console.WriteLine("Thread {0} doing work", thread);
        Random rng = new Random(thread); // Seed with unique numbers
        Thread.Sleep(rng.Next(2000));
        Console.WriteLine("Thread {0} done", thread);
    }
}
