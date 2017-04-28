using System;
using System.Data;
using System.Reflection;
using System.Collections.Generic;

// mcs /r:System.Data.dll Extension.cs
static class MyExtensions
{
    // this method allows any object to display the assembly
    // it is defined in.
    public static void DisplayDefiningAssembly(this object obj)
    {
        Console.WriteLine("{0} lives here: => {1}", obj.GetType().Name,
                Assembly.GetAssembly(obj.GetType()).GetName().Name);
    }
    
    // this method allows any integer to reverse its digits
    public static int ReverseDigits(this int i)
    {
        // Translate int into a string, and get all chars
        char[] digits = i.ToString().ToCharArray();
        Array.Reverse(digits);
        string newDigits = new string(digits);
        return int.Parse(newDigits);
    }
}

// Interface Extensions
static class AnnoyingExtensions
{
    public static void PrintDataAndBeep(this System.Collections.IEnumerable iterator)
    {
        foreach (var item in iterator)
        {
            Console.WriteLine(item);
            Console.Beep();
        }
    }
}

class Client
{
    public static void TextAnnoyingExtensions()
    {
        Console.WriteLine("Extending interface compatible types");
        string[] data = {"Wow", "this", "is", "sort", "of", "annoying",
                         "but", "in", "a", "weird", "way", "fun"};
        data.PrintDataAndBeep();
        Console.WriteLine();
        // List<t> implements IEnumerable!
        List<int> myInts = new List<int>() {10, 15, 20};
        myInts.PrintDataAndBeep();
    }

    public static void TestMyExtensions()
    {
        // the int has assumed a new identity
        int myInt = 12345678;
        myInt.DisplayDefiningAssembly();

        // so has the DataSet
        System.Data.DataSet d = new System.Data.DataSet();
        d.DisplayDefiningAssembly();

        // and the SoundPlayer
        System.Media.SoundPlayer sp = new System.Media.SoundPlayer();
        sp.DisplayDefiningAssembly();

        // use new integer functionality
        Console.WriteLine("Value of myInt: {0}", myInt);
        Console.WriteLine("Reversed digits of myInt: {0}", myInt.ReverseDigits());
    }

    public static void Main()
    {
        //TestMyExtensions();
        TextAnnoyingExtensions();
    }
}
