using System;

class Employee
{
    private string _name;
    private string _password;
    private int _id;
    // getter and setters in classes
    public string Name {
        get { return _name; }
        set { _name = value; }
    }
    //readonly
    public string Name2 {
        get { return _name; }
    }
    // writeonly
    public string Password {
        set { 
            if (value.Length > 7) {
                _password = value; 
                Console.WriteLine("passwd: {0}", _password);
            } else {
                throw new Exception("passwd must be at least 7 chars");
            }
        }
    }
    // methods
    public void Login(string loginName, string password)
    {
    }
    // ctors
    public Employee(string name)
    {
        Console.WriteLine("ctor - default {0}", name);
        _name = name;
    }
    public Employee(int id)
        : this("dude")
    {
        _id = id;
        Console.WriteLine("ctor id: {0}", id);
    }
    // dtor
    ~Employee()
    {
        Console.WriteLine("dtor");
    }
}

public class Tester
{
    public static void Main()
    {
        Employee e = new Employee(7);
        Console.WriteLine("hello");
        e.Name = "The dude";
        e.Password = "noooddddles";
        Console.WriteLine("my name is: {0}", e.Name);
    }
}
