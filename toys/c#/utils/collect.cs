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
        // Output: chinook coho pink sockeye

        var map = new Dictionary<string, string>();
        map.Add("txt", "notepad.exe");
        map.Add("bmp", "paint.exe");
        map.Add("dib", "paint.exe");
        map.Add("rtf", "wordpad.exe");

        foreach( var kvp in map ) {
            Console.WriteLine("Key = {0}, Value = {1}", kvp.Key, kvp.Value);
        }

    }
}
