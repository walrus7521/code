using System;

class UserLog
{
    private static int _userCount;
    public static void IncrementUserCount()
    {
        _userCount++;
    }
    public static void DecrementUserCount()
    {
        _userCount--;
    }
    public static int UserCount {
        get { return _userCount; }
    }
}

public class User
{
    public void Login(string userName, string password)
    {
        UserLog.IncrementUserCount();
    }
}

class Client
{
    public static void Main()
    {
        User u1 = new User();
        u1.Login("cindy","123");
        Console.WriteLine(UserLog.UserCount);
        User u2 = new User();
        u2.Login("bart","456");
        Console.WriteLine(UserLog.UserCount);
        User u3 = new User();
        u3.Login("rowdy","789");
        Console.WriteLine(UserLog.UserCount);
    }
}
