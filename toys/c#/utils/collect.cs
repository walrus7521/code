using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Security.Cryptography.X509Certificates;
using System.Text;

// build method
// $ mcs hello.cs
// $ mono hello.exe

public class Hello1
{
   public static void Main()
   {
        // Create a list of strings.
        var salmons = new List<string>();
        salmons.Add("chinook");
        salmons.Add("coho");
        salmons.Add("pink");
        salmons.Add("sockeye");

        // Iterate through the list.
        foreach (var fish in salmons) {
            Console.Write(fish + " ");
        }
        Console.WriteLine();
        // Output: chinook coho pink sockeye

        var map = new Dictionary<string, string>();
        map.Add("txt", "notepad.exe");
        map.Add("bmp", "paint.exe");
        map.Add("dib", "paint.exe");
        map.Add("rtf", "wordpad.exe");

        foreach(var kvp in map) {
            Console.WriteLine("Key = {0}, Value = {1}", kvp.Key, kvp.Value);
        }
        Console.WriteLine();

        var al = new ArrayList();
        // Add puts it at the end
        // Insert(0, xxx); puts at beginning
        al.Add(45);
        al.Add(78);
        al.Add(33);
        al.Add(56);
        al.Add(12);
        al.Add(23);
        al.Add(9);
        al.Insert(0, 9); // puts it at front
         
        // array list is similar to C++ vector
        for (int i = 0; i < al.Count; i++) {
            Console.Write(al[i] + " ");
        }
        Console.WriteLine();

        foreach (var i in al)
        {
            Console.Write(i + " ");
        }
        Console.WriteLine();

    }
}
