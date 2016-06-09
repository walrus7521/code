using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

// Enforce CLS compliance for all public types in this assembly
[assembly: CLSCompliant(true)]


// custom attribute
[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct,
        Inherited = false)]
public sealed class VehicleDescriptionAttribute : System.Attribute
{
    public string Description { get; set; }
    public VehicleDescriptionAttribute(string vehicleDescription)
    {
        Description = vehicleDescription;
    }
    public VehicleDescriptionAttribute(){}
}

[Serializable]
[VehicleDescriptionAttribute(Description = "My rocking Harley")]
public class Motorcycle
{
    public Motorcycle(){}
    // this field will not be persisted
    [NonSerialized]
    float weightOfCurrentPassengers;

    // these fields are still serializable
    //[VehicleDescriptionAttribute("this is illegal..")]
    bool hasRadioSystem;
    bool hasHeadSet;
    bool hasSissyBar;
}

[Serializable]
[Obsolete("Use another vehicle!")]
[VehicleDescriptionAttribute("The old gray mare, she aint' what she used to be...")]
public class HorseAndBuggy
{
    public HorseAndBuggy(){}
}

[VehicleDescriptionAttribute("A very long, slow, but feature-rich auto")]
public class Winnebago
{
    public ulong notCLSCompliant;
}

public class Client
{

    public static void ReflectOnAttributesLateBinding()
    {
        Console.WriteLine("****** Reflect on Attributes Late Binding ******");
        try
        {
            Assembly asm = Assembly.Load("AttributedCarLibrary");

            // get type info
            Type vehicleDesc = asm.GetType("Attributes.VehicleDescriptionAttribute");
            // get type info of description property
            PropertyInfo propDesc = vehicleDesc.GetProperty("Description");

            // get all types
            Type[] types = asm.GetTypes();
            foreach (Type t in types) {
                object[] objs = t.GetCustomAttributes(vehicleDesc, false);

                foreach (object o in objs) {
                    Console.WriteLine("-> {0}: {1}",
                            t.Name, propDesc.GetValue(o, null));
                }
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }

    }

    public static void ReflectOnAttributesEarlyBinding()
    {
        Console.WriteLine("****** Reflect on Attributes Early Binding ******");
        // get a type representing Winnebago
        Type t = typeof(Winnebago);

        // get all attributes on the Winnebago
        object[] customAtts = t.GetCustomAttributes(false); // false means don't go all up the inheritance chain

        foreach (VehicleDescriptionAttribute v in customAtts) {
            Console.WriteLine("attrib ->{0}", v.Description);
        }
    }


    static void Main()
    {
        HorseAndBuggy hb = new HorseAndBuggy();
        Motorcycle mc = new Motorcycle();
        Winnebago win = new Winnebago();
        ReflectOnAttributesEarlyBinding();
        ReflectOnAttributesLateBinding();
    }
}
