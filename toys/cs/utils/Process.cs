using System;
using System.Linq;
using System.Diagnostics;

public class Client
{

    static void StartAndKillProcess2(string proc, string arg)
    {
        Process ieProc = null;
        // launch a process and go to facebook.com
        try
        {
            ProcessStartInfo startInfo = new
                ProcessStartInfo(proc, arg);
            startInfo.WindowStyle = ProcessWindowStyle.Maximized;
            ieProc = Process.Start(startInfo);
        }
        catch (InvalidOperationException ex)
        {
            Console.WriteLine(ex.Message);
        }
        Console.WriteLine("--> Hit enter key to kill {0}...", ieProc.ProcessName);
        Console.ReadLine();
        // kill it
        try
        {
            ieProc.Kill();
        }
        catch (InvalidOperationException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }

    static void StartAndKillProcess(string proc, string arg)
    {
        Process ieProc = null;
        // launch a process and go to facebook.com
        try
        {
            ieProc = Process.Start(proc, arg);
        }
        catch (InvalidOperationException ex)
        {
            Console.WriteLine(ex.Message);
        }
        Console.WriteLine("--> Hit enter key to kill {0}...", ieProc.ProcessName);
        Console.ReadLine();
        // kill it
        try
        {
            ieProc.Kill();
        }
        catch (InvalidOperationException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }

    static void EnumModsForPid(int pID)
    {
        Process theProc = null;
        try
        {
            theProc = Process.GetProcessById(pID);
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
            return;
        }
        // list modules
        Console.WriteLine("modules loaded by {0}", theProc.ProcessName);
        ProcessModuleCollection theMods = theProc.Modules;
        foreach (ProcessModule pm in theMods) {
            string info = 
                string.Format("-> Mod Name: {0}", pm.ModuleName);
            Console.WriteLine(info);
        }
        Console.WriteLine("****************************************\n");
    }

    static void EnumThreadsForPid(int pID)
    {
        Process theProc = null;
        try
        {
            theProc = Process.GetProcessById(pID);
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
            return;
        }
        // list stats
        Console.WriteLine("threads used by {0}", theProc.ProcessName);
        ProcessThreadCollection theThreads = theProc.Threads;
        foreach (ProcessThread pt in theThreads) {
            string info = 
                string.Format("-> Thread ID: {0}", pt.Id);
            //string info = 
            //    string.Format("-> Thread ID: {0}\tStart Time: {1}\tPriority: {2}",
            //            pt.Id, pt.StartTime.ToShortTimeString(), pt.PriorityLevel);
            Console.WriteLine(info);
        }
        Console.WriteLine("****************************************\n");
    }

    static void ListAllRunningProcesses()
    {
        // Get all the processes on the local machine, ordered by PID.
        var runningProcs = 
            from proc in Process.GetProcesses(".") orderby proc.Id select proc;

        foreach (var p in runningProcs) {
            string info = string.Format("-> PID: {0}\tName: {1}",
                    p.Id, p.ProcessName);
            Console.WriteLine(info);
        }
        Console.WriteLine("****************************************\n");
    }

    static void Main()
    {
        //ListAllRunningProcesses();
        //EnumThreadsForPid(297);
        //EnumModsForPid(297);
        //StartAndKillProcess("/Applications/Safari.app/Contents/MacOS/Safari", "www.facebook.com");
        StartAndKillProcess2("/Applications/Safari.app/Contents/MacOS/Safari", "www.facebook.com");
    }

}
