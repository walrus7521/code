using System;
using System.Net;
using System.Net.Sockets;

class Env_and_IPAddressExample {

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

    static void PrintHostInfo(String host) 
    {
        try {
            IPHostEntry hostInfo;
            hostInfo = Dns.GetHostEntry(host);
            Console.WriteLine("Canonical Name: " + hostInfo.HostName);

            Console.Write("IP Address: " );
            foreach (IPAddress ipaddr in hostInfo.AddressList) {
                Console.Write(ipaddr.ToString() + " ");
            }
            Console.WriteLine();
            Console.Write("Aliases:     ");
            foreach (String alias in hostInfo.Aliases) {
                Console.Write(alias + " ");
            }
            Console.WriteLine();
        } catch (Exception) {
            Console.WriteLine("unable to resolve host: " + host);
        }

    }

    static void Main(string[] args) {
        try {
            Console.WriteLine("Show environment: ");
            ShowEnvDetails();
            Console.WriteLine("Local host: ");
            String localHostName = Dns.GetHostName();
            Console.WriteLine("Host name:  " + localHostName);
            PrintHostInfo(localHostName);
        } catch (Exception) {
            Console.WriteLine("unable to resolve local host\n");
        }


    }
}
