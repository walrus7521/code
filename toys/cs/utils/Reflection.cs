using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CarLibrary;

// mcs ch14CarCli.cs /r:ch14CarLib.dll
// or if the assembly is an .exe
// mcs mcs Reflection.cs ch14CarLib.cs ch14CarDerived.cs 

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

            Type t = viper.GetType(); // need instance of class here
            Console.WriteLine("sports car type: {0}", t);
            Type t2 = typeof(SportsCar); // no need to have instance of class here
            Console.WriteLine("sports car type2: {0}", t2);
        }
    }
}
