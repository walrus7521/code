using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Reflection;
using System.IO;

namespace ExtReflector
{
    class Program
    {

        static void DisplayTypesInAsm(Assembly asm)
        {
            Console.WriteLine("****** types in Assembly ******");
            Console.WriteLine("->{0}", asm.FullName);
            Type[] types = asm.GetTypes();
            foreach (Type t in types) {
                Console.WriteLine("Type: {0}", t);
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("****** External Assembly Viewer ******");
            string asmName = "";
            Assembly asm = null;

            do {
                Console.WriteLine("\nEnter an assembly to evaluate");
                Console.Write("or enter Q to quit: ");

                asmName = Console.ReadLine();
                if (asmName.ToUpper() == "Q")
                {
                    break;
                }

                try {
                    asm = Assembly.Load(asmName);
                    //asm = Assembly.LoadFrom(asmName); // for absolute path
                    DisplayTypesInAsm(asm);
                } catch {
                    Console.WriteLine("Sorry, can't find assembly");
                }

            } while (true);
        }

    }


}

