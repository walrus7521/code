using System;

public class Changer {

    public Changer(int[] a) {
        A = new int[a.Length];
        len = a.Length;
        for (int i = 0; i < len; ++i) {
            A[i] = a[i];
        }
        Array.Sort(A);
    }

    public void Max() {
        Console.WriteLine("recursive");
        Max_r(0,0);
        Console.WriteLine("iterative");
        Max_i();
    }

    private void Max_i() {
        int running = 0, max = 0;
        for (int i = 0; i < len; ++i) {
            max = running+1;
            running += A[i];
            if (A[i] > max) {
                break;
            }
        }
        Console.WriteLine("max = {0}", max);
    }

    private void Max_r(int curr, int running)
    {
        int max = running+1;
        running += A[curr];
        if (A[curr] > max) {
            Console.WriteLine("max = {0}", max);
            return;
        }
        Max_r(curr+1, running);
    }

    public void Show() {
        for (int i = 0; i < len; ++i) {
            Console.WriteLine("a[{0}] = {1}", i, A[i]);
        }
    }

    private int[] A;
    private int len;
}

public class concrete
{
    public static void Main() {
        int[] a = {12,2,1,15,2,4};
        Changer chgr = new Changer(a);
        chgr.Show();
        chgr.Max();
   }
}


