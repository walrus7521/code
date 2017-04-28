using System;

class Grok {

    static void swap(int[] a, int i, int j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    
    static int [] selection(int [] arr)
    {
        int n = arr.Length;
        for (int i = 0; i < n; i++) {
            int min = i;
            for (int j = i+1; j < n; j++) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            swap(arr, i, min);
        }
        return arr;
    }

    static void show(int [] a)
    {
        foreach (int i in a) {
            System.Console.Write("{0} ", i);
        }
        System.Console.WriteLine("");
    }

    public static void Main(string [] args)
    {
        int [] arr = {5,3,6,2,10};
        int [] b = selection(arr);
        show(b);
    }
}
