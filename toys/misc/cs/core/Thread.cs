using System;
using System.Threading;
using System.Runtime.Remoting.Contexts;

public class Alpha
{
    // This method that will be called when the thread is started
    public void Beta()
    {
        while (true)
        {
            Console.WriteLine("Alpha.Beta is running in its own thread.");
            Thread.Sleep(5000);
        }
    }
};

public class Simple
{
    public static void AlphaTest()
    {
        Console.WriteLine("Thread Start/Stop/Join Sample");
        Alpha oAlpha = new Alpha();
        // Create the thread object, passing in the Alpha.Beta method
        // via a ThreadStart delegate. This does not start the thread.
        Thread oThread = new Thread(new ThreadStart(oAlpha.Beta));
        // Start the thread
        oThread.Start();
        // Spin for a while waiting for the started thread to become
        // alive:
        if (oThread.IsAlive) Console.WriteLine("thread is running...");
        // Put the Main thread to sleep for 1 millisecond to allow oThread
        // to do some work:
        Thread.Sleep(1000);
        // Request that oThread be stopped
        if (oThread.IsAlive) Console.WriteLine("thread is still running...");
        oThread.Abort(); // this will kill the thread
        if (!oThread.IsAlive) Console.WriteLine("thread is dead...");
        // Wait until oThread finishes. Join also has overloads
        // that take a millisecond interval or a TimeSpan object.
        oThread.Join(); // not sure what this does to a dead thread
        Console.WriteLine("Alpha.Beta has finished");
        try 
        {
            Console.WriteLine("Try to restart the Alpha.Beta thread");
            oThread.Start();
        }
        catch (ThreadStateException) 
        {
            Console.Write("ThreadStateException trying to restart Alpha.Beta. ");
            Console.WriteLine("Expected since aborted threads cannot be restarted.");
        }
    }

    public delegate int BinaryOp(int x, int y);
    static int Add(int x, int y)
    {
        Console.WriteLine("Add() on thread Id: {0}", Thread.CurrentThread.ManagedThreadId);
        Thread.Sleep(5000);
        return x + y;
    }

    public static void SyncDelegate()
    {
        Console.WriteLine("SyncDelegate() on thread Id: {0}", Thread.CurrentThread.ManagedThreadId);
        BinaryOp b = new BinaryOp(Add);
        int z = b(1, 2);
        Console.WriteLine("SyncDelegate() z = {0}", z);
    }

    public static void AsyncDelegate()
    {
        Console.WriteLine("AsyncDelegate() on thread Id: {0}", Thread.CurrentThread.ManagedThreadId);
        BinaryOp b = new BinaryOp(Add);
        IAsyncResult iar = b.BeginInvoke(1, 2, null, null);
        //while (!iar.IsCompleted) {
        //    Console.WriteLine("doing more foreground work...");
        //    Thread.Sleep(1000);
        //}
        while (!iar.AsyncWaitHandle.WaitOne(1000, true)) {
            Console.WriteLine("doing more foreground work...");
        }
        int z = b.EndInvoke(iar);
        Console.WriteLine("AsyncDelegate() z = {0}", z);
    }

    public static void FunWithThreads()
    {
        // get the currently executing context
        Thread currThread = Thread.CurrentThread;
        Console.WriteLine("Thread: {0}", currThread.ToString());
        Console.WriteLine("Id: {0}", currThread.ManagedThreadId.ToString());
        // get the domain
        AppDomain ad = Thread.GetDomain();
        Console.WriteLine("Domain: {0}", ad);
        // get the current thread context
        Context ctx = Thread.CurrentContext;
        Console.WriteLine("Context: {0}", ctx);
    }

    public static int Main()
    {
        //FunWithThreads();
        //SyncDelegate();
        //AsyncDelegate();
        AlphaTest();
        return 0;
    }
}
