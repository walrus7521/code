// SwapTest.cs
// Copyright (c) 2015, HerongYang.com, All Rights Reserved.

using System;

// candidate for singleton
public class Swapper {
    static void Swap<T>(ref T x, ref T y)
    {
         T t = y;
         y = x;
         x = t;
    }
}

public class SwapTest {
   public static void Main() {
      string a = "Herong";
      string b = "Yang";
      Console.WriteLine("{0} {1}", a, b);
      Swapper.Swap<int>(ref a, ref b);
      Console.WriteLine("{0} {1}", a, b);
   }
}
