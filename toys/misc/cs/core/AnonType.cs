using System;

class Program
{
    static void ReflectOverAnonymousType(object obj)
    {
        Console.WriteLine("obj is an instance of: {0}", obj.GetType().Name);
        Console.WriteLine("Base class of {0} is {1}", obj.GetType().Name, obj.GetType().BaseType);
        // anonymous types automatically get ToString overriden to string of member name/value pairs
        Console.WriteLine("obj.ToString() == {0}", obj.ToString());
        Console.WriteLine("obj.GetHashCode() == {0}", obj.GetHashCode());
    }

    static void BuildAnonType(string make, string color, int currSp)
    {
        var car = new {Make = make, Color = color, Speed = currSp };
        // note you can now use this type to get the property data!
        Console.WriteLine("You have a {0} {1} going {2} MPH",
                car.Color, car.Make, car.Speed);

        // anon types have custom implmentations of each virtual
        // method of System.Object, e.g.
        Console.WriteLine("ToString() == {0}", car.ToString());

    }

    static void EqualityTest()
    {
        var firstCar = new {Color = "Bright Pink", Make = "Saab", CurrentSpeed = 55 };
        var secondCar = new {Color = "Bright Pink", Make = "Saab", CurrentSpeed = 55 };

        if (firstCar.Equals(secondCar)) {
            Console.WriteLine("same anonymous object!");
        } else {
            Console.WriteLine("not the same anonymous object!");
        }

        if (firstCar == secondCar) {
            Console.WriteLine("same anonymous object!");
        } else {
            Console.WriteLine("not the same anonymous object!");
        }
        if (firstCar.GetType().Name == secondCar.GetType().Name) {
            Console.WriteLine("same anonymous object!");
        } else {
            Console.WriteLine("not the same anonymous object!");
        }
        ReflectOverAnonymousType(firstCar);
        ReflectOverAnonymousType(secondCar);
    }

    static void LayeredAnonType()
    {
        var purchaseItem = new {
            TimeBought = DateTime.Now,
            ItemBought = new {
                Color = "Red", Make = "Saab", CurrentSpeed = 55
            },
            Price = 34.000
        };
        Console.WriteLine("purchase = {0}", purchaseItem.ToString());
    }

    static void Main(string[] args)
    {
        Console.WriteLine("**** fun with anon types ***** ");
        var myCar = new {Color = "Bright Pink", Make = "Saab", CurrentSpeed = 55 };
        // now show the car
        Console.WriteLine("My car is a {0} {1}", myCar.Color, myCar.Make);
        // now call helper to build anonymous type via args
        BuildAnonType("BMW", "Black", 90);
        ReflectOverAnonymousType(myCar);
        EqualityTest();
        LayeredAnonType();
    }
}
