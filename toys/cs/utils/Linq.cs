using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

public class Client
{
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

    static void Main()
    {
        QueryOverStrings();
        QueryOverInts();
    }



}
