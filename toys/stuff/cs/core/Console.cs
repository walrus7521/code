using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
 
 
class FallingRocksSolo
{
    static void ResetBuffer()
    {
        Console.BufferHeight = Console.WindowHeight = 30;
        Console.BufferWidth = Console.WindowWidth = 60;
    }
 
    static void PrintAtPosition(int x, int y, char symbol, ConsoleColor color)
    {
        Console.SetCursorPosition(x, y);
        Console.ForegroundColor = color;
        Console.Write(symbol);
    }
 
    static void PrintStringAtPosition(int x, int y, string text, ConsoleColor color)
    {
        Console.SetCursorPosition(x, y);
        Console.ForegroundColor = color;
        Console.Write(text);
    }
 
    struct Unit
    {
        public int x;
        public int y;
        public ConsoleColor color;
        public char symbol;
    }
 
    static void Main()
    {
        Console.WriteLine("buffer height " + Console.BufferHeight);
        Console.WriteLine("buffer width  " + Console.BufferWidth);
        Console.WriteLine("window height " + Console.WindowHeight);
        Console.WriteLine("window width  " + Console.WindowWidth);
    }
}
