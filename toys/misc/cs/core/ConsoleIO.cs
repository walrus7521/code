using System;

class Program
{
    static void GetUserData()
    {
        Console.Write("Please enter your name: ");
        string userName = Console.ReadLine();
        Console.Write("Please enter your age: ");
        string userAge = Console.ReadLine();

        // change colors
        ConsoleColor prevColor = Console.ForegroundColor;
        Console.ForegroundColor = ConsoleColor.Yellow;

        Console.WriteLine("Hello {0}!  You are {1} years old.",
                userName, userAge);
        //restore color
        Console.ForegroundColor = prevColor;
    }
    
    static void Main(string[] args)
    {
        Console.WriteLine("***** Basic Console I/O *****\a");
        GetUserData();
        Console.ReadLine();
    }
}
