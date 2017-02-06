
using System;

class Sort
{

    static void SwapInts(int[] array, int position1, int position2)
    {
        //
        // Swaps elements in an array.
        //
        int temp = array[position1]; // Copy the first position's element
        array[position1] = array[position2]; // Assign to the second element
        array[position2] = temp; // Assign to the first element
    }

    public static void show(int[] a)
    {
        for (int i = 0; i < a.Length; i++) {
            Console.Write("{0}, ", a[i]);
        }
        Console.WriteLine();
    }

    public static void selection(int[] a)
    {
        int min;
        int n = a.Length;
        for (int i = 0; i < n-1; i++) {
            min = i;
            for (int j = i+1; j < n; j++) {
                if (a[min] > a[j]) {
                    min = j;
                }
            }
            if (i != min) {
                SwapInts(a, i, min);
            }
        }
    }

    public static void bubble(int[] a)
    {
        int n = a.Length;
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-1-i; j++) {
                if (a[j+1] < a[j]) {
                    SwapInts(a, j, j+1);
                }
            }
        }
    }
    
    public static void merge(int[] a, int p, int q, int r)
    {
    }

    public static void partition(int[] a, int low, int high)
    {
    }

    public static void merge_sort(int[] a)
    {
        partition(a, 0, a.Length-1);
    }


  
    public static int sequential(int[] a, int first, int last, int k)
    {
        int i = first;
        int n = last - first;
        while (a[i] != k) {
            ++i;
        }
        if (i < n) return i;
        else return -1;
    }

    public static void Main()
    {
        int[] a = new int[7]{9, 4, 7, 3, 6, 2, 1};
        //int[] a = new int[5]{45, 68, 89, 34, 29};
        //int[] a = new int[4]{5, 4, 3, 2};
        int find = 7;

        int got_it = sequential(a, 0, a.Length, find);
        if (got_it > 0) {
            Console.WriteLine("found {0} at index {1}", find, got_it);
        } else {
            Console.WriteLine("could not find {0}", find);
        }



        show(a);
        //selection(a);
        //bubble(a);
        merge_sort(a);
        show(a);

    } 
}

