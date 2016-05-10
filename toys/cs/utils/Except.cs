using System;
using System.IO;

class Except
{
    public void LogOrder(long orderNumber, DateTime orderDate)
    {
        try
        {
            if (orderDate > DateTime.Now)
            {
                throw new ApplicationException("order date can not be in the future.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("LogOrder: exception " + ex.Message);
        }
    }

    public static string ReadText(string filePath)
    {
        StreamReader sr = null;
        try
        {
            sr = File.OpenText(filePath);
            string fileText = sr.ReadToEnd();
            Console.WriteLine("return");
            return fileText;
        }
        catch (DirectoryNotFoundException ex)
        {
            return ex.Message;
        }
        catch (FileNotFoundException ex)
        {
            return ex.Message;
        }
        catch (Exception ex)
        {
            return ex.Message;
        }
        finally
        {
            if (sr != null)
            {
                Console.WriteLine("finally");
                sr.Close();
                sr.Dispose();
            }
        }
    }

    public static void DivByZero()
    {
        int x = 1;
        int y = 0;
        int z = 0;
        try
        {
            try
            {
                z = x / y;
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine("divzero: " + e.Message);
                z = 0;
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("outer: " + e.Message);
        }

        Console.WriteLine("ok z = " + z);
    }

    public static void Main()
    {
        string path = "mutex.cs";
        string data = ReadText(path);
        Console.WriteLine(data);
        DivByZero();
    }
}
