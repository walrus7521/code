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
    // virtual makes method selectively (not mandatory) overrideable
    public virtual int GetTheDude()
    {
        return _dude;
    }
    // virtual makes method selectively (not mandatory) overrideable
    public virtual void SetTheDude(int value)
    {
        _dude = value;
    }
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
    // select method to override
    // make it non-overridable by derived of Derived2
    public sealed override int GetTheDude()
    {
        int dude = base.GetTheDude();
        return dude + 69;
    }
}


class Client
{
    public static void Main()
    {
        Derived1 d1 = new Derived1();
        d1.Prop = 7;
        Console.WriteLine(d1);
        Base1 b1 = new Base1();
        Console.WriteLine(b1);

        Derived2 d2 = new Derived2();
        Base2 b2 = new Base2();
        d2.SetTheDude(77);
        Console.WriteLine(d2.GetTheDude());
    }
}
