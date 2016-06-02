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

class ProductInfo
{
    public string Name {get;set;}
    public string Description {get;set;}
    public int NumberInStock {get;set;}
    public override string ToString()
    {
        return string.Format("Name={0}, Description={1}, Number in Stock={2}",
                Name, Description, NumberInStock);
    }
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

    static void TestLinqOverGenericCollections()
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

    static void TestLinqOverNonGenericCollections()
    {
        Console.WriteLine("***** LINQ over Non Generic Collections *****");
        List<Car> myCars = new List<Car>() {
            new Car{PetName = "Henry",   Color = "Silver", Speed = 100, Make = "BMW"},
            new Car{PetName = "Daisy",   Color = "Tan", Speed = 90, Make = "BMW"},
            new Car{PetName = "Mary",    Color = "Black", Speed = 55, Make = "VW"},
            new Car{PetName = "Clunker", Color = "Rust", Speed = 5, Make = "Yugo"},
            new Car{PetName = "Melvin",  Color = "White", Speed = 43, Make = "Ford"},
        };
        var myCarsEnum = myCars.OfType<Car>();
        var fastCars = from c in myCarsEnum where c.Speed>55 select c;
        foreach (var car in fastCars) {
            Console.WriteLine("{0} is going too fast!", car.PetName);
        }
    }

    static void FilteringDataUsingOfType()
    {
        Console.WriteLine("***** LINQ Filtering Data using OfType *****");
        ArrayList myStuff = new ArrayList(); // non-generic holds objects
        myStuff.AddRange(new object[] {10, 400, 8, false, new Car(), "string data"});
        // now filter out the numeric data
        var myInts = myStuff.OfType<int>();
        foreach (var i in myInts) {
            Console.WriteLine("Int value: {0}", i);
        }
    }

    // use LINQ queries using ProductInfo
    static void QueriesUsingLINQ()
    {
        Console.WriteLine("****** Queries with LINQ Expressions *****");
        ProductInfo[] products = new[] {
            new ProductInfo{ Name="Mac's Coffee", Description="Coffee with TEETH", NumberInStock=24 },
            new ProductInfo{ Name="Milk Maid Mild", Description="Milk cows love", NumberInStock=100 },
            new ProductInfo{ Name="Pure Silk Tofu", Description="Bland as possible", NumberInStock=120 },
            new ProductInfo{ Name="Crunchy Pops", Description="Cheezy, peppery good", NumberInStock=2 },
            new ProductInfo{ Name="RipOff Water", Description="From tap to wallet", NumberInStock=100 },
            new ProductInfo{ Name="Classic Valpo Pizza", Description="Everyone's pizza", NumberInStock=73 },
        };
        // Basic selection syntax
        // get everything
        var allProducts = from p in products select p;
        foreach (var prod in allProducts) {
            Console.WriteLine(prod.ToString());
        }
        
        // Just grab the Name
        var names = from p in products select p.Name;
        foreach (var n in names) {
            Console.WriteLine("Name: {0}", n);
        }

        // Obtaining subsets of data - using "where"
        // get items with 25 or more in stock
        Console.WriteLine("overstock items");
        var overstock = from p in products where p.NumberInStock > 25 select p;
        foreach (var c in overstock) {
            Console.WriteLine(c.ToString());
        }

        // query over names and descriptions and project results onto anonymous type
        Console.WriteLine("project query to anonymous type");
        var nameDesc = from p in products select new { p.Name, p.Description };
        foreach (var item in nameDesc) {
            Console.WriteLine(item.ToString());
        }

        // transform the anonymous projection into Array in case we need to return it
        Console.WriteLine("transform anonymous projection to Array");
        var nameDescArray = nameDesc.ToArray(); // note no use of <> as we don't know underlying type
        foreach (var item in nameDescArray) {
            Console.WriteLine(item.ToString());
        }

        // obtaining counts using Enumerable
        int count = nameDescArray.Count();
        Console.WriteLine("Query returned {0} items", count);

        // Reverse the set
        Console.WriteLine("Reverse the results");
        foreach (var item in nameDesc.Reverse()) {
            Console.WriteLine(item.ToString());
        }

        // Sort the results by alpha products
        var sortProducts = from p in products orderby p.Name ascending select p;
        Console.WriteLine("Query in sorted fashion");
        foreach (var item in sortProducts) {
            Console.WriteLine(item.ToString());
        }

        // LINQ as a better Venn diagramming tool
        Console.WriteLine("LINQ as a better Venn diagramming tool");
        List<string> myCars = new List<string> { "Yugo", "Aztec", "BMW" };
        List<string> yourCars = new List<string> { "BMW", "Saab", "Aztec" };
        var carDiff = (from c in myCars select c)
            .Except(from c2 in yourCars select c2);
        Console.WriteLine("Here is what you don't have, but I do:");
        foreach (string s in carDiff) {
            Console.WriteLine(s); // prints Yugo
        }

        var carIntersect = (from c in myCars select c)
            .Intersect(from c2 in yourCars select c2);
        Console.WriteLine("Here is what we have in common:");
        foreach (string s in carIntersect) {
            Console.WriteLine(s);
        }

        var carUnion = (from c in myCars select c)
            .Union(from c2 in yourCars select c2);
        Console.WriteLine("Here is what we both have, no duplicates (union):");
        foreach (string s in carUnion) {
            Console.WriteLine(s);
        }

        var carConcat = (from c in myCars select c)
            .Concat(from c2 in yourCars select c2);
        Console.WriteLine("Here is the concatenation of what we have:");
        foreach (string s in carConcat) {
            Console.WriteLine(s);
        }

        Console.WriteLine("Here is a dedup of what we have in common:");
        foreach (string s in carConcat.Distinct()) {
            Console.WriteLine(s);
        }

        // Aggregation operations
        Console.WriteLine("Aggregation operations:");
        double[] winterTemps = { 2.0, -21.3, 8, -4, 0, 8.2 };
        Console.WriteLine("Max temp: {0}",
            (from t in winterTemps select t).Max());
        Console.WriteLine("Min temp: {0}",
            (from t in winterTemps select t).Min());
        Console.WriteLine("Average temp: {0}",
            (from t in winterTemps select t).Average());
        Console.WriteLine("Sum temp: {0}",
            (from t in winterTemps select t).Sum());

    }

    static void QueryStringWithOperators()
    {
        Console.WriteLine("***** Using Query Operators *****");
        string[] videoGames = { "Morrowind", "Uncharted 2", "Fallout 3",
                "Daxter", "System Shock 2" };
        var subset = from game in videoGames where game.Contains(" ") orderby 
            game select game;
        foreach (string s in subset) {
            Console.WriteLine("Item: {0}", s);
        }
    }

    static void QueryExpressionsUsingEnumerableTypeAndLambdaExpressions()
    {
        Console.WriteLine("***** Using Enumerable / Lambda Expressions *****");
        string[] videoGames = { "Morrowind", "Uncharted 2", "Fallout 3",
                "Daxter", "System Shock 2" };

        var subset = videoGames.Where(game => game.Contains(" "))
            .OrderBy(game => game).Select(game => game);

        foreach (var game in subset) {
            Console.WriteLine("Item: {0}", game);
        }
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
        TestLinqOverGenericCollections();
        TestLinqOverNonGenericCollections();
        FilteringDataUsingOfType();
        QueriesUsingLINQ();
        QueryStringWithOperators();
        QueryExpressionsUsingEnumerableTypeAndLambdaExpressions();
    }



}
