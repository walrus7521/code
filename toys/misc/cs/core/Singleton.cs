using System;

// multithread safe singleton

public sealed class Singleton
{
   private static volatile Singleton instance;
   private static object syncRoot = new Object();
   private Singleton() {}
   public static Singleton Instance {
      get {
         if (instance == null) {
            lock (syncRoot) {
               if (instance == null) 
                  instance = new Singleton();
            }
         }
         return instance;
      }
   }
   public void Api1() {
       Console.WriteLine("api1");
   }
   public void Api2() {
       Console.WriteLine("api2");
   }
}
 
class Test {
    static void Main(String[] args) {
        Singleton.Instance.Api1();
        Singleton.Instance.Api2();
    }
}
