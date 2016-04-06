// SwapTest.cs
// Copyright (c) 2015, HerongYang.com, All Rights Reserved.

using System;
public class SwapTest {
   public static void Main() {
      string a = "Herong";
      string b = "Yang";
      Console.WriteLine("{0} {1}", a, b);
      Util.Swap(ref a, ref b);
      Console.WriteLine("{0} {1}", a, b);
   }
}
