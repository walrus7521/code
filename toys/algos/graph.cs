using System.Collections.Generic;
using System;

public class graph
{
    public static void Main(string[] args)
    {
        int[,] array = new int[,]
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        // Get upper bounds for the array
        int rows = array.GetUpperBound(0);
        int cols = array.GetUpperBound(1);

        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j <= cols; j++) {
                Console.WriteLine(array[i,j]);
            }
        }
    }
}

