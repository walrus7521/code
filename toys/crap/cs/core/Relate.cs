using System;

// For two objects, Foo and Bar the relationships can be defined
public class Bar {
    public override string ToString()
    {
        return "Bar";
    }
}

// 1. Association - I have a relationship with an object.  Foo uses Bar
public class Foo_Assoc { 
    void Baz(Bar bar) {
    } 
    public override string ToString()
    {
        return "Foo_Assoc";
    }
};

// 2. Composition - I own an object and I am responsible for its lifetime, when Foo dies, so does Bar
public class Foo_Comp {
    private Bar bar = new Bar(); 
    public override string ToString()
    {
        return "Foo_Comp";
    }
}

// 3. Aggregation - I have an object borrowed from someone else. When Foo dies, Bar may live on.
public class Foo_Aggr { 
    private Bar bar; 
    public Foo_Aggr(Bar bar) { 
       this.bar = bar; 
    }
    public override string ToString()
    {
        return "Foo_Aggr";
    }
}

public class Client
{
    public static void Main()
    {
        Bar bar = new Bar();
        Foo_Assoc foo_as = new Foo_Assoc();
        Foo_Comp  foo_co = new Foo_Comp();
        Foo_Aggr  foo_ag = new Foo_Aggr(bar);
        Console.WriteLine(bar);
        Console.WriteLine(foo_as);
        Console.WriteLine(foo_co);
        Console.WriteLine(foo_ag);
    }
}
