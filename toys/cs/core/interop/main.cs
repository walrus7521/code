using System;
using System.Runtime.InteropServices;     // DLL support

class Program
{

    static void Main(string[] args)
    {
        int f = func1(33);
        Console.WriteLine("**** fun with interop ***** {0}", f);
        
        IntPtr p = func2(44);
        string mstr = Marshal.PtrToStringAnsi(p);
        Console.WriteLine("**** fun with interop ***** {0}", mstr);
    }


    [DllImport("libfoo.so", CallingConvention = CallingConvention.Cdecl)]
    public static extern int func1(int fault);
    [DllImport("libfoo.so", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr func2(int fault);
    
}
