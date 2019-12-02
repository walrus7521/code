using System;
using System.Linq;
using System.Reflection;

public class Program
{
    static void ListMethods(Type t)
    {
        Console.WriteLine("**** Methods *****");
        var methodNames = from n in t.GetMethods() select n.Name;
        foreach (var name in methodNames) {
            Console.WriteLine("->{0}", name);
        }
    }

    static void ListMethods2(Type t)
    {
        Console.WriteLine("**** Methods 2 *****");
        var methodNames = from n in t.GetMethods() select n;
        foreach (var name in methodNames) {
            Console.WriteLine("->{0}", name);
        }
    }

    static void ListMethods3(Type t)
    {
        Console.WriteLine("****** Methods 3 ******");
        MethodInfo[] mi = t.GetMethods();
        foreach (var m in mi) {
            string retVal = m.ReturnType.FullName;
            string paramInfo = "(";
            foreach (ParameterInfo pi in m.GetParameters()) {
                paramInfo += string.Format("{0} {1} ", pi.ParameterType, pi.Name);
            }
            paramInfo += ")";
            Console.WriteLine("->{0} {1} {2}", retVal, m.Name, paramInfo);
        }
    }

    static void ListFields(Type t)
    {
        Console.WriteLine("***** Fields *****");
        var fieldNames = from f in t.GetFields() select f.Name;
        foreach (var name in fieldNames) {
            Console.WriteLine("->{0}", name);
        }
    }

    static void ListProps(Type t)
    {
        Console.WriteLine("***** Properties *****");
        var propNames = from p in t.GetProperties() select p.Name;
        foreach (var name in propNames) {
            Console.WriteLine("->{0}", name);
        }
    }

    static void ListInterfaces(Type t)
    {
        Console.WriteLine("***** Interfaces *****");
        var ifaces = from i in t.GetInterfaces() select i;
        foreach (var i in ifaces) {
            Console.WriteLine("->{0}", i.Name);
        }
    }
    
    static void ListVariousStats(Type t)
    {
        Console.WriteLine("****** Various Statistics ******");
        Console.WriteLine("Base class is: {0}", t.BaseType);
        Console.WriteLine("Is type abstract? {0}", t.IsAbstract);
        Console.WriteLine("Is type sealed? {0}", t.IsSealed);
        Console.WriteLine("Is type generic? {0}", t.IsGenericTypeDefinition);
        Console.WriteLine("Is type a class type? {0}", t.IsClass);
    }

    static void Main()
    {
        string typeName = "";
        do {
            Console.WriteLine("\nEnter a type name to evaluate");
            Console.WriteLine("or enter Q to quit: ");
            
            typeName = Console.ReadLine();

            if (typeName.ToUpper() == "Q") {
                break;
            }

            try {
                Type t = Type.GetType(typeName);
                Console.WriteLine("");
                ListVariousStats(t);
                ListFields(t);
                ListProps(t);
                ListMethods(t);
                ListMethods2(t);
                ListMethods3(t);
                ListInterfaces(t);
            } catch {
                Console.WriteLine("Sorry, can't find type {0}", typeName);
            }
        } while (true);
    }
}
