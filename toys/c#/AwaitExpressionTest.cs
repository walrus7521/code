// AwaitExpressionTest.cs
// Copyright (c) 2015, HerongYang.com, All Rights Reserved.

using System;
using System.Net.Http;
using System.Threading.Tasks;
public class AwaitExpressionTest {
   static void Main() {
      Console.WriteLine("Before 'await' ...");	
      AwaitTest();
      Console.WriteLine("After 'await' ...");	
   } 
   async static void AwaitTest() {
      string uri = "http://www.herongyang.com/Service/Hello_REST.php";
      HttpClient c = new HttpClient();
      Console.WriteLine("Calling GetStringAsync()...");	
      Task<string> t = c.GetStringAsync(uri);
      Console.WriteLine("Evaluating await-expression ...");	
      string s = await t;
      Console.WriteLine("Writing task result ...");	
      Console.WriteLine(s);
   } 
}

