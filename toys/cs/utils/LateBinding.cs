using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Reflection;
using System.IO;

public class Program
{

    static void CreateUsingLateBinding(Assembly asm)
    {
        try
        {
            // get meta data
            Type miniVan = asm.GetType("CarLibrary.MiniVan");
            // create miniVan object on the fly
            object obj = Activator.CreateInstance(miniVan);
            Console.WriteLine("Created a {0} using late binding!", obj);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }

    static void Main(string[] args)
    {
        Console.WriteLine("****** Fun with Late Binding ******");
        // try loading a local copy of CarLibrary.dll
        Assembly a = null;
        try
        {
            a = Assembly.Load("ch14CarLib");
        }
        catch (FileNotFoundException e)
        {
            Console.WriteLine(e.Message);
            return;
        }
        if (a != null) 
        {
            CreateUsingLateBinding(a);
        }
    }

}
