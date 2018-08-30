// AwaitExpressionTest.cs
// Copyright (c) 2015, HerongYang.com, All Rights Reserved.

// mcs /r:System.Net.Http.dll AwaitExpressionTest.cs

using System;
using System.Net.Http;
using System.Threading.Tasks;

public class AwaitExpressionTest {
    static void Main() 
    {
        var t1 = Task.Factory.StartNew(new Func<Task>(async () => await DoMethod())).Unwrap();
        Console.WriteLine("STARTED");
        t1.Wait();
    } 

    static async Task DoMethod()
    {
        Console.WriteLine("Before 'await' ...");	
        await AwaitTest();
        Console.WriteLine("After 'await' ...");	
    }

    static async Task AwaitTest() {
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

