using System;
using System.Linq;
using System.Diagnostics;

class Client
{
    static void ListAllRunningProcesses()
    {
        var runningProcs = 
            from proc in Process.GetProcesses(".") orderby proc.Id select proc;

        foreach (var p in runningProcs)
        {
            string info = string.Format("-> PID: {0}\tName: {1}",
                    p.Id, p.ProcessName);
            Console.WriteLine(info);
        }
        Console.WriteLine("*************************\n");
    }

    public static void Main()
    {
        ListAllRunningProcesses();
    }
}
