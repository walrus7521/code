using System;
using System.Collections.Generic;

public class libs
{
   public static void Main()
   {

        List<string> colors = new List<string>();
        colors.Add("Red");
        colors.Add("Blue");
        colors.Add("Green");

        foreach (string color in colors) {
            System.Console.WriteLine(color);
        }
   }
}
