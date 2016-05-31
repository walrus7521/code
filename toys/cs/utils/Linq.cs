using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

// applying Linq queries to Collection objects
class Car
{
    public string PetName {get;set;}
    public string Color {get;set;}
    public int Speed {get;set;}
    public string Make {get;set;}
}



public class Client
{

    // returning Linq result via Immediate Execution
    // allows to return a string[] rather than IEnumerable<string>
    static string[] GetStringSubsetAsArray()
    {
        string[] colors = {"Light Red", "Green",
                           "Yellow", "Dark Red", "Red", "Purple"};

        // note subset is an IEnumerable<string>-compatible object
        var theRedColors = from c in colors 
            where c.Contains("Red") select c;

        // map results into an array
        return theRedColors.ToArray();
    }

    // return a Linq query result from method
    static IEnumerable<string> GetStringSubset()
    {
        string[] colors = {"Light Red", "Green",
                           "Yellow", "Dark Red", "Red", "Purple"};

        // note subset is an IEnumerable<string>-compatible object
        IEnumerable<string> theRedColors = from c in colors 
            where c.Contains("Red") select c;

        return theRedColors;
    }

    static void ReflectOverQueryResults(object resultSet)
    {
        Console.WriteLine("**** info about query ****");
        Console.WriteLine("resultSet is of type: {0}", resultSet.GetType().Name);
        Console.WriteLine("resultSet location: {0}", resultSet.GetType().Assembly.GetName().Name);
    }

    static void QueryOverInts()
    {
        Console.WriteLine("**** query over ints ****");
        int[] numbers = {10, 20, 30, 40, 1, 2, 3, 8};
        // print only items less than 10
        IEnumerable<int> subset = from i in numbers where i<10 select i;
        var subset2 = from i in numbers where i<10 select i;
        int[] subsetAsIntArray = 
            (from i in numbers where i<10 select i).ToArray<int>();

        List<int> subsetAsListOfInts = 
            (from i in numbers where i<10 select i).ToList<int>();

        
        foreach (var i in subset2) {
            Console.WriteLine("Item: {0}", i);
        }
        ReflectOverQueryResults(subset2);
    }

    static void QueryOverStrings()
    {
        Console.WriteLine("**** query over strings ****");
        string[] currentVideoGames = {"Morrowind", "Uncharted 2",
                                      "Fallout 3", "Daxter", "System Shock 2"};
        // build a query finding items with embedded spaces
        IEnumerable<string> subset = from g in currentVideoGames
                                     where g.Contains(" ") orderby g select g;
        // print results
        foreach (string s in subset) {
            Console.WriteLine("Item: {0}", s);
        }
        ReflectOverQueryResults(subset);
    }

    static void GetFastCars(List<Car> myCars)
    {
        Console.WriteLine("***** LINQ over Fast Cars *****");
        var fastCars = from c in myCars where c.Speed > 55 select c;
        foreach (var car in fastCars) {
            Console.WriteLine("{0} is going too fast!", car.PetName);
        }
    }

    static void GetFastBMWs(List<Car> myCars)
    {
        Console.WriteLine("***** LINQ over Fast BMWs *****");
        var fastCars = from c in myCars where c.Speed > 90  && c.Make == "BMW" select c;
        foreach (var car in fastCars) {
            Console.WriteLine("{0} is going too fast!", car.PetName);
        }
    }

    static void TestLinqOverCollections()
    {
        Console.WriteLine("***** LINQ over Generic Collections *****");
        List<Car> myCars = new List<Car>() {
            new Car{PetName = "Henry",   Color = "Silver", Speed = 100, Make = "BMW"},
            new Car{PetName = "Daisy",   Color = "Tan", Speed = 90, Make = "BMW"},
            new Car{PetName = "Mary",    Color = "Black", Speed = 55, Make = "VW"},
            new Car{PetName = "Clunker", Color = "Rust", Speed = 5, Make = "Yugo"},
            new Car{PetName = "Melvin",  Color = "White", Speed = 43, Make = "Ford"},
        };
        GetFastCars(myCars);
        GetFastBMWs(myCars);
    }

    static void Main()
    {
        //QueryOverStrings();
        //QueryOverInts();
        // example of getting a result from a method
        IEnumerable<string> subset = GetStringSubset();
        foreach (string item in subset) {
            Console.WriteLine(item);
        }
        string[] subset2 = GetStringSubsetAsArray();
        foreach (string item in subset2) {
            Console.WriteLine(item);
        }
        TestLinqOverCollections();
    }



}
