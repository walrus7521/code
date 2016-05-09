using System;
using System.Net;
using System.Net.Sockets;

class IPAddressExample {
    static void PrintHostInfo(String host) {
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
            Console.WriteLine("Local host: ");
            String localHostName = Dns.GetHostName();
            Console.WriteLine("Host name:  " + localHostName);
            PrintHostInfo(localHostName);
        } catch (Exception) {
            Console.WriteLine("unable to resolve local host\n");
        }


    }
}
