using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CarLibrary;

// mcs ch14CarCli.cs /r:ch14CarLib.dll
// or if the assembly is an .exe
// mcs ch14CarCli.cs /r:ch14CarLib.exe

namespace CSharpCarClient
{
    public class Program
    {
        static void Main()
        {
            Console.WriteLine("****** c# CarLibrary client app ******");
            SportsCar viper = new SportsCar("Viper", 240, 40);
            viper.TurboBoost();

            MiniVan mv = new MiniVan();
            mv.TurboBoost();

        }
    }
}
