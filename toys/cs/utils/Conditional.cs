using System;

class Client
{
    
    public static int Compare(int v1, int v2)
    {
        return v1<v2 ? -1 : v1>v2 ? +1 : 0;
    }

    public static void Main()
    {
        int v1, v2, v3;
        v1 = 4; v2 = 6;
        v3 = Compare(v1, v2);
        Console.WriteLine("Compare(" + v1 + ", " + v2 + ") = " + v3);
        v1 = 6; v2 = 4;
        v3 = Compare(v1, v2);
        Console.WriteLine("Compare(" + v1 + ", " + v2 + ") = " + v3);
        v1 = 6; v2 = 6;
        v3 = Compare(v1, v2);
        Console.WriteLine("Compare(" + v1 + ", " + v2 + ") = " + v3);
    }
}
