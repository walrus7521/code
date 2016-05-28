using System;

public class Point : ICloneable
{
    public int X {get;set;}
    public int Y {get;set;}

    public Point(int xPos, int yPos) { X = xPos; Y = yPos; }
    public Point() {}

    // override Object ToString
    public override string ToString()
    {
        return string.Format("X = {0}; Y = {1}", X, Y);
    }

    public object Clone()
    {
        //return new Point(this.X, this.Y);
        // or, since (if) the class contains no references, you can simply return this
        // if there are references, it will do a memberwise shallow copy resulting in 
        // the copy getting the refs, and not a new object.
        // to support true deep copy, new instances of the refs need to be created during
        // the cloning process.
        return this.MemberwiseClone();
    }
}

public class PointDescription
{
    public string PetName {get;set;}
    public Guid PointID {get;set;}

    public PointDescription()
    {
        PetName = "No-name";
        PointID = Guid.NewGuid();
    }
}

public class Point2 : ICloneable
{
    public int X {get;set;}
    public int Y {get;set;}
    public PointDescription desc = new PointDescription();

    public Point2(int xPos, int yPos, string PetName) 
    { X = xPos; Y = yPos; desc.PetName = PetName; }
    public Point2(int xPos, int yPos) 
    { X = xPos; Y = yPos; }
    public Point2() {}

    // override Object ToString
    public override string ToString()
    {
        return string.Format("X = {0}; Y = {1}; Name = {2}; \nID = {3}", 
                X, Y, desc.PetName, desc.PointID);
    }

    public object Clone()
    {
        // now we need to make a deep copy, start with shallow
        Point2 newPoint = (Point2) this.MemberwiseClone();
        // now fill in the gaps.
        PointDescription currentDesc = new PointDescription();
        currentDesc.PetName = this.desc.PetName;
        newPoint.desc = currentDesc;
        return newPoint;
    }
}

class Client
{
    public static void Main()
    {
        Point p1 = new Point(50, 50);
        Point p2 = p1;
        p2.X = 0;
        Console.WriteLine(p1);
        Console.WriteLine(p2);

        Point p3 = new Point(100, 100);
        Point p4 = (Point) p3.Clone();
        p4.Y = 0;
        Console.WriteLine(p3);
        Console.WriteLine(p4);

        Point2 p5 = new Point2(100, 100, "Jane");
        Point2 p6 = (Point2) p5.Clone();
        Console.WriteLine(p5);
        Console.WriteLine(p6);
        p6.desc.PetName = "My new Point2";
        p6.X = 9;
        Console.WriteLine(p5);
        Console.WriteLine(p6);

    }
}
