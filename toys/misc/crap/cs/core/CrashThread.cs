// CrashThread.cs
// Copyright (c) 2015, HerongYang.com, All Rights Reserved.

using System;
using System.Threading;
public class CrashThread {
   public static void Main() {
      Console.Write("Press ENTER to continue:");
      Console.ReadLine();

      int count = 1000;
      Thread t; 
      for (int n=1; n<=count; n++) {
         t = new Thread(Run);
         t.Start();
         Console.WriteLine(System.DateTime.Now.TimeOfDay +": Launched thread "+n);
      }
   }
   public static void Run() {
      while(true);
   }
}
