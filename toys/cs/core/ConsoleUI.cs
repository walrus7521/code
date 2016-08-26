using System;


class FallingRocksSolo
{

    const ConsoleColor BACKGROUND_COLOR = ConsoleColor.Green;
    const string cellLeftTop = "┌";
    const string cellRightTop = "┐";
    const string cellLeftBottom = "└";
    const string cellRightBottom = "┘";
    const string cellHorizontalJointTop = "┬";
    const string cellHorizontalJointbottom = "┴";
    const string cellVerticalJointLeft = "├";
    const string cellTJoint = "┼";
    const string cellVerticalJointRight = "┤";
    const string cellHorizontalLine = "─";
    const string cellVerticalLine = "│";


    static int tableWidth = 77;

    static void PrintLine()
    {
        Console.Write(cellLeftTop);
        Console.Write(new string('-', tableWidth));
        Console.Write(cellRightTop);
    }

    static void PrintRow(params string[] columns)
    {
        int width = (tableWidth - columns.Length) / columns.Length;
        string row = "|";

        Console.Write(cellLeftTop);
        foreach (string column in columns)
        {
            row += AlignCentre(column, width) + "|";
        }

        Console.WriteLine(row);
    }

    static string AlignCentre(string text, int width)
    {
        text = text.Length > width ? text.Substring(0, width - 3) + "..." : text;

        if (string.IsNullOrEmpty(text))
        {
            return new string(' ', width);
        }
        else
        {
            return text.PadRight(width - (width - text.Length) / 2).PadLeft(width);
        }
    }

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
 
    static void SetBackgroundColor() {
        Console.BackgroundColor = BACKGROUND_COLOR;
        Console.Clear(); //Important!
    }
 
    static void Main()
    {
        //Console.WriteLine("buffer height " + Console.BufferHeight);
        //Console.WriteLine("buffer width  " + Console.BufferWidth);
        //Console.WriteLine("window height " + Console.WindowHeight);
        //Console.WriteLine("window width  " + Console.WindowWidth);
        SetBackgroundColor();
        //PrintStringAtPosition(10, 10, "hello", ConsoleColor.Red);
        string[] cols = {"id", "name", "info"};
        string[] emptycols = {"", "", ""};
        PrintRow(emptycols);
        PrintRow(cols);
        PrintRow(emptycols);
        PrintLine();
        PrintRow(emptycols);
        PrintRow(cols);
        PrintRow(emptycols);
        PrintLine();
        PrintRow(emptycols);
        PrintRow(cols);
        PrintRow(emptycols);
        PrintLine();


        ConsoleKeyInfo keyInfo;
        while ((keyInfo = Console.ReadKey(true)).Key != ConsoleKey.Escape) {
            if (keyInfo.Key.ToString() == "Q") {
                Console.BackgroundColor = ConsoleColor.Black;
                Console.Clear(); //Important!
                Environment.Exit(0);
            }
        } 
    }
}
