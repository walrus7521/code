using System;

class Client {

    [Flags]
    public enum FileAccess {
        Read  = 1 << 0,
        Write = 1 << 1
    }

    public static void Write(FileAccess access) {
        if (0 != (access & FileAccess.Write)) {
            Console.WriteLine("you have write permission");
        }
    }

    public static void Main()
    {
        FileAccess access = FileAccess.Read | FileAccess.Write;
        Console.WriteLine(access);
        Write(access);
    }

}
