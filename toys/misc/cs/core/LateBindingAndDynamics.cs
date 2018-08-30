using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Reflection;
using System.IO;

// Note use this app with Dynaics.dll
//
public class Program
{

    private static void AddWithReflection()
    {
        Assembly asm = Assembly.Load("Dynamics"); //  has SimpleMath
        try
        {
            Type math = asm.GetType("DynamicsUtils.SimpleMath");
            if (math != null) {
                Console.WriteLine("Type {0}", math);
            } else {
                Console.WriteLine("Type math is null");
            }
            object obj = Activator.CreateInstance(math);
            MethodInfo mi = math.GetMethod("Add");
            object[] args = {10, 70};
            Console.WriteLine("Result is: {0}", mi.Invoke(obj, args));
        }
        catch (Exception ex)
        {
            Console.WriteLine("yo messed up: " + ex.Message);
        }
    }

    private static void AddWithDynamic()
    {
        Assembly asm = Assembly.Load("Dynamics"); //  has SimpleMath
        try
        {
            Type math = asm.GetType("DynamicsUtils.SimpleMath");
            if (math != null) {
                Console.WriteLine("Type {0}", math);
            } else {
                Console.WriteLine("Type math is null");
            }
            dynamic obj = Activator.CreateInstance(math);
            Console.WriteLine("Result is: {0}", obj.Add(1,1));
        }
        catch (Exception ex)
        {
            Console.WriteLine("yo messed up: " + ex.Message);
        }
    }

    static void CreateUsingLateBinding(Assembly asm)
    {
        Console.WriteLine("****** Call method using late binding ******");
        try
        {
            // get meta data
            Type miniVan = asm.GetType("CarLibrary.MiniVan");
            // create miniVan object on the fly
            object obj = Activator.CreateInstance(miniVan);
            Console.WriteLine("Created a {0} using late binding!", obj);

            MethodInfo mi = miniVan.GetMethod("TurboBoost");
            // invoke the method
            mi.Invoke(obj, null);

            MethodInfo mi2 = miniVan.GetMethod("TurnOnRadio");
            mi2.Invoke(obj, new object[] { true, 2 });

        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }

    // re-write using dynamic
    static void InvokeMethodWithDynamicKeyword(Assembly asm)
    {
        Console.WriteLine("****** Call method using dynamics ******");
        try
        {
            // get meta data
            Type miniVan = asm.GetType("CarLibrary.MiniVan");
            // create miniVan object on the fly
            dynamic obj = Activator.CreateInstance(miniVan);
            Console.WriteLine("Created a {0} using dynamics!", obj);
            // invoke the method
            obj.TurboBoost();
            obj.TurnOnRadio(true, 0);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
    
    static void Main(string[] args)
    {
        Console.WriteLine("****** Fun with Late Binding ******\n");
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
            //CreateUsingLateBinding(a);
            //Console.WriteLine();
            //InvokeMethodWithDynamicKeyword(a);
            //AddWithReflection();
            AddWithDynamic();

        }
    }

}
