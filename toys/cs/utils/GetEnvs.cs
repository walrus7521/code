using System;

class Client
{
   static void ShowEnvDetails()
   {
       // print drives on this machine
       foreach (var drive in Environment.GetLogicalDrives())
       {
           Console.WriteLine("Drive: {0}", drive);
       }
       Console.WriteLine("User Name: {0}", Environment.UserName);
       Console.WriteLine("Machine Name: {0}", Environment.MachineName);
       Console.WriteLine("OS: {0}", Environment.OSVersion);
       Console.WriteLine("Num processors: {0}", Environment.ProcessorCount);
       Console.WriteLine(".NET Version: {0}", Environment.Version);
   }

    public static int Main(string[] args)
    {
        ShowEnvDetails();

        Console.ReadLine();
        return -1;
    }
}
