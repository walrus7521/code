using System;
using System.IO;
using System.Linq;
using System.Reflection;

class Program
{
    static void InitDAD(AppDomain domain)
    {
        // this prints out the name of any assembly
        // loaded into the domain, after it has been
        // created.
        domain.AssemblyLoad += (o, s) =>
        {
            Console.WriteLine("\n{0} has just now been loaded!!\n", s.LoadedAssembly.GetName().Name);
        };

        domain.ProcessExit += (o, s) =>
        {
            Console.WriteLine("\nAD has just been unloaded!!\n");
        };
    }

    static void UnloadAppDomain(AppDomain domain)
    {
        AppDomain.Unload(domain);
    }

    static void MakeNewAppDomain() // and load a DLL
    {
        Console.WriteLine("Creating a new domain!!*****");
        AppDomain newAD = AppDomain.CreateDomain("SecondAppDomain");

        try
        {
            // load DLL
            newAD.Load("ch14CarLib");
        }
        catch (FileNotFoundException ex)
        {
            Console.WriteLine(ex.Message);
        }

        ListAllAssembliesInAppDomain2(newAD);
        UnloadAppDomain(newAD);
    }

    static void ListAllAssembliesInAppDomain2(AppDomain domain)
    {
        var loadedAssemblies = from a in domain.GetAssemblies() 
            orderby a.GetName().Name select a;

        Console.WriteLine("**** Here are the assemblies loaded in {0} ******\n",
                domain.FriendlyName);
        foreach (var a in loadedAssemblies) {
            Console.WriteLine("-> Name: {0}", a.GetName().Name);
            Console.WriteLine("-> Version: {0}", a.GetName().Version);
        }
    }

    static void ListAllAssembliesInAppDomain(AppDomain domain)
    {
        Assembly[] loadedAssemblies = domain.GetAssemblies();
        Console.WriteLine("**** Here are the assemblies loaded in {0} ******\n",
                domain.FriendlyName);
        foreach (Assembly a in loadedAssemblies) {
            Console.WriteLine("-> Name: {0}", a.GetName().Name);
            Console.WriteLine("-> Version: {0}", a.GetName().Version);
        }
    }

    static void DisplayDADStats(AppDomain domain)
    {
        // Get access to the AppDomain for the current thread
        Console.WriteLine("Name of this domain: {0}", domain.FriendlyName);
        Console.WriteLine("ID of domain in this process: {0}", domain.Id);
        Console.WriteLine("Is this the default domain?: {0}", domain.IsDefaultAppDomain());
        Console.WriteLine("Base Directory of this domain: {0}", domain.BaseDirectory);
    }

    static void Main()
    {
        AppDomain defaultAD = AppDomain.CurrentDomain;
        Console.WriteLine("******* AppDomain stuff ******");
        InitDAD(defaultAD);
        DisplayDADStats(defaultAD);
        ListAllAssembliesInAppDomain(defaultAD);
        ListAllAssembliesInAppDomain2(defaultAD);
        MakeNewAppDomain();
    }
}
