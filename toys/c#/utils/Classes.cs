using System;

class Base1
{
    private int _prop;
    private int _dude;
    public int Prop {
        get { return _prop; }
        set { _prop = value; }
    }
    public override string ToString()
    {
        return "Base1: " + _prop;
    }
}

class Base2
{
    private int _prop;
    protected int _dude;
    public int Prop {
        get { return _prop; }
        set { _prop = value; }
    }
    public override string ToString()
    {
        return "Base2: " + _prop;
    }
}

class Derived1 : Base1
{
}

class Derived2 : Base2
{
}


class Client
{
    public static void Main()
    {
        Derived1 d1 = new Derived1();
        d1.Prop = 7;
        Console.WriteLine(d1);
        Base1 b1 = new Base1();
        b1._dude = 77;
        Console.WriteLine(b1);

        Derived2 d2 = new Derived2();
        Base2 b2 = new Base2();
        b2._dude = 77;
        Console.WriteLine(b2);
    }
}
