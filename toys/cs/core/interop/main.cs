using System;
using System.Runtime.InteropServices;     // DLL support

class Program
{

    static void Main(string[] args)
    {
        //string response = "MCP having issues? " + nfault;
        //mcp_str = mcp_get_fault(nfault);
        int f = func(33);
        Console.WriteLine("**** fun with interop ***** {0}", f);
        
        //string mstr = Marshal.PtrToStringAnsi(mcp_str);
    }

    //[DllImport("FaultLib.dll", CallingConvention = CallingConvention.Cdecl)]
    //public static extern IntPtr mcp_get_fault(int fault);

    [DllImport("libfoo.so", CallingConvention = CallingConvention.Cdecl)]
    public static extern int func(int fault);
    
}
