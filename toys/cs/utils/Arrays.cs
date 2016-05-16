using System;

// Array rank is the number of dimensions
public class Client
{
    static void ArrayInfo(String name, Array a)
    {
        Console.Write("{0} has length={1} rank={2} [", name, a.Length, a.Rank);
        for (int i = 0, stop=a.Rank; i<stop; i++)
            Console.Write(" {0}", a.GetLength(i));
        Console.WriteLine(" ]");
    }

    public static void Main()
    {
        double[,] r2 = new double[3,2];
        for (int i=0; i<3; i++)
            for (int j=0; j<2; j++)
                r2[i,j] = i + 0.1 * j;

        double[][] t2 = { new double[] {0.0},
                          new double[] {1.0, 1.1},
                          new double[] {2.0, 2.1, 2.2}};

        ArrayInfo("r2", r2);
        ArrayInfo("t2", t2);

        r2.SetValue(10.0, 1, 0);
        r2.SetValue(21.0, 2, 1);
        ((double[])t2.GetValue(1)).SetValue(10.0, 0);
        ((double[])t2.GetValue(2)).SetValue(21.0, 1);
        foreach (var d in r2)
            Console.Write(d + " ");
        Console.WriteLine();
    }

}
