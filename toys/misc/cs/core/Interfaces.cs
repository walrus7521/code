using System;

public interface IPointy
{
    //byte GetNumberOfPoints();
    // read-write property
    // retType PropName { ge; set; }
    // write-only property
    // retType PropName { set; }
    // read-only property
    byte Points { get; }
    // event
    // indexer
}

public interface IDraw3D
{
    void Draw3D();
}

public abstract class Shape
{
    //public Shape(){}
    public Shape(string name = "NoName") { PetName = name; }
    public abstract void Draw();
    public string PetName { get; set; }
    protected string name;
}

public class Triangle : Shape, IPointy
{
    public Triangle() {}
    public Triangle(string name) : base(name) {}
    public override void Draw()
    { Console.WriteLine("Drawing {0} the Triangle", PetName); }

    // IPointy implementation
    public byte Points
    {
        get { return 3; }
    }
}
 
class Hexagon : Shape, IPointy, IDraw3D
{
    public Hexagon() {}
    public Hexagon(string name) : base(name) {}
    public override void Draw()
    { Console.WriteLine("Drawing {0} the Hexagon", PetName); }

    // IPointy implementation
    public byte Points
    {
        get { return 6; }
    }
    // IDraw3D implementation
    public void Draw3D()
    {
        Console.WriteLine("Drawing Hexagon in 3D");
    }
}

class Circle : Shape
{
    public Circle() {}
    public Circle(string name) : base(name) {}
    public override void Draw()
    { Console.WriteLine("Drawing {0} the Circle", PetName); }

}

class ThreeDCircle : Circle, IDraw3D
{
    // IDraw3D implementation
    public void Draw3D()
    {
        Console.WriteLine("Drawing Circle in 3D");
    }
}

class Knife : IPointy
{
    // IPointy implementation
    public byte Points
    {
        get { return 1; }
    }
}

class Fork : IPointy
{
    // IPointy implementation
    public byte Points
    {
        get { return 4; }
    }
}

class PitchFork : IPointy
{
    // IPointy implementation
    public byte Points
    {
        get { return 3; }
    }
}

// multiple interfaces with same name, so need to resolve the name clash
public interface IDrawToForm
{
    void Draw();
}

public interface IDrawToMemory
{
    void Draw();
}

public interface IDrawToPrinter
{
    void Draw();
}

class Octagon : IDrawToForm, IDrawToMemory, IDrawToPrinter
{
    // explicit interface implementation syntax
    void IDrawToForm.Draw()
    {
        Console.WriteLine("Drawing the Octagon to Form...");
    }
    void IDrawToMemory.Draw()
    {
        Console.WriteLine("Drawing the Octagon to Memory...");
    }
    void IDrawToPrinter.Draw()
    {
        Console.WriteLine("Drawing the Octagon to Printer...");
    }
}

// Interface Hierarchy
public interface IDrawable
{
    void Draw();
}
// now lets extend IDrawable
public interface IAdvancedDraw : IDrawable
{
    void DrawInBoundingBox(int top, int left, int bottom, int right);
    void DrawUpsideDown();
}
// classes the implement IAdvancedDraw must implement both interfaces
public class BitmapImage : IAdvancedDraw
{
    public void Draw()
    {
        Console.WriteLine("Drawing...");
    }
    public void DrawInBoundingBox(int top, int left, int bottom, int right)
    {
        Console.WriteLine("Drawing in a box...");
    }
    public void DrawUpsideDown()
    {
        Console.WriteLine("Drawing upside down...");
    }
}


// multiple inheritance with interfaces
interface IPrintable
{
    void Print();
    void Draw(); // note possible name clash here 
}
// now do multiple inheritance
interface IShape : IDrawable, IPrintable
{
    int GetNumberOfSides();
}
class Snickerdoodle : IShape
{
    public int GetNumberOfSides() { return 44; }
    //void IDrawable.Draw()
    //{
    //    Console.WriteLine("Drawing snickerdoodle...");
    //}
    public void Draw()
    {
        Console.WriteLine("Drawing snickerdoodle...");
    }
    public void Print()
    {
        Console.WriteLine("Printing snickerdoodle...");
    }
}
class Muffin : IShape
{
    public int GetNumberOfSides() { return 42; }
    void IDrawable.Draw()
    {
        Console.WriteLine("IDrawable Drawing Muffin...");
    }
    void IPrintable.Draw()
    {
        Console.WriteLine("IPrintable Drawing Muffin...");
    }
    public void Print()
    {
        Console.WriteLine("Printing Muffin...");
    }
}

class Program
{

    public static void Main()
    {
        Hexagon hex = new Hexagon("James");
        Circle c = new Circle("Lisa");
        IPointy itfPt = null;
        try
        {
            // dynamic test if interface is supported.
            itfPt = (IPointy) c;
            Console.WriteLine(itfPt.Points);
        } 
        catch (InvalidCastException e)
        {
            Console.WriteLine(e.Message);
        }

        // or use "as" keyword to see interfaces supported.
        Hexagon hex2 = new Hexagon("Peter");
        IPointy itfPt2 = hex2 as IPointy;
        if (itfPt2 != null)
            Console.WriteLine("YES! Points: {0}", itfPt2.Points);
        else
            Console.WriteLine("OOPS! Not pointy...");

        // or check for implemented interface using "is" keyword
        Shape[] shapes = { new Hexagon(), new Circle(),
                           new Triangle("Joe"), new Triangle("JoJo")};

        for (int i = 0; i < shapes.Length; i++) {
            shapes[i].Draw();
            // who's pointy
            if (shapes[i] is IPointy) {
                Console.WriteLine("-> Points: {0}", ((IPointy) shapes[i]).Points);
            } else {
                Console.WriteLine("-> {0} is not pointy!", shapes[i].PetName);
            }
        }

        IPointy[] pointies = { new Hexagon(), new Knife(), new Triangle(),
                               new Fork(), new PitchFork()};

        foreach (IPointy i in pointies) {
            Console.WriteLine("Object has {0} points.",
                    i.Points);
        }
        
        // resolving name clashes
        Octagon oct = new Octagon();
        IDrawToForm ifrm = (IDrawToForm) oct;
        ifrm.Draw();
        IDrawToMemory imem = (IDrawToMemory) oct;
        imem.Draw();
        IDrawToPrinter iprt = (IDrawToPrinter) oct;
        iprt.Draw();
        // must use casting to access the interface method
        ((IDrawToPrinter)oct).Draw();
        if (oct is IDrawToMemory) {
            ((IDrawToMemory)oct).Draw();
        }

        // using BitmapImage invoke each method at object level
        // as well as extract reference to supported interface
        BitmapImage bm = new BitmapImage();
        bm.Draw();
        bm.DrawInBoundingBox(10, 10, 100, 150);
        bm.DrawUpsideDown();
        // get IAdvancedDraw explicitly
        IAdvancedDraw iad = bm as IAdvancedDraw;
        if (iad != null) {
            iad.DrawUpsideDown();
        }

        // multiple inheritance
        Snickerdoodle sn = new Snickerdoodle();
        sn.Draw();
        sn.Print();

        Muffin mf = new Muffin();
        ((IDrawable)mf).Draw();
        ((IPrintable)mf).Draw();
        mf.Print();
        mf.GetNumberOfSides();

    }

}
