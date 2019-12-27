using System;
using System.Threading;
using System.Threading.Tasks;

// see https://msdn.microsoft.com/en-us/library/dd537609(v=vs.110).aspx

public class TaskSamples
{

    static void Task1() {
        Thread.CurrentThread.Name = "Main";
        // Create a task and supply a user delegate by using a lambda expression. 
        Task taskA = new Task( () => Console.WriteLine("Hello from taskA."));
        taskA.Start();
        Console.WriteLine("Hello from thread '{0}'.", Thread.CurrentThread.Name);
        taskA.Wait();
   }

   public static void Main()
   {
       Task1();
   }
}
