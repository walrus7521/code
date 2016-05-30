using System;

public class Point
{
    public int X { get; set; }
    public int Y { get; set; }

    public Point(int xPos, int yPos)
    {
        X = xPos;
        Y = yPos;
    }

    // unaries
    public static Point operator ++ (Point p)
    {
        return new Point(p.X + 1, p.Y + 1);
    }

    public static Point operator -- (Point p)
    {
        return new Point(p.X - 1, p.Y - 1);
    }

    // binaries
    public static Point operator - (int delta, Point p)
    {
        return new Point(p.X - delta, p.Y - delta);
    }

    public static Point operator + (int delta, Point p)
    {
        return new Point(p.X + delta, p.Y + delta);
    }

    public static Point operator - (Point p, int delta)
    {
        return new Point(p.X - delta, p.Y - delta);
    }

    public static Point operator + (Point p, int delta)
    {
        return new Point(p.X + delta, p.Y + delta);
    }

    public static Point operator - (Point p1, Point p2)
    {
        return new Point(p1.X - p2.X, p1.Y - p2.Y);
    }

    public static Point operator + (Point p1, Point p2)
    {
        return new Point(p1.X + p2.X, p1.Y + p2.Y);
    }

    public override string ToString()
    {
        return string.Format("[{0}, {1}]", this.X, this.Y);
    }
}

public struct Complex 
{
   public int real;
   public int imaginary;

   public Complex(int real, int imaginary) 
   {
      this.real = real;
      this.imaginary = imaginary;
   }

   // Declare which operator to overload (+), the types 
   // that can be added (two Complex objects), and the 
   // return type (Complex):
   public static Complex operator +(Complex c1, Complex c2) 
   {
      return new Complex(c1.real + c2.real, c1.imaginary + c2.imaginary);
   }
   // Override the ToString method to display an complex number in the suitable format:
   public override string ToString()
   {
      return(String.Format("{0} + {1}i", real, imaginary));
   }
}

class Client
{
    public static void TestPoint()
    {
        Console.WriteLine("Test points");
        Point ptOne = new Point(100, 100);
        Point ptTwo = new Point(40, 40);
        Point ptThree = new Point(90, 5);
        Point ptFour = new Point(0, 500);
        Console.WriteLine("ptOne = {0}", ptOne);
        Console.WriteLine("ptTwo = {0}", ptTwo);

        // add points
        Console.WriteLine("ptOne + ptTwo: {0} ", ptOne + ptTwo);
        // subtract points
        Console.WriteLine("ptOne - ptTwo: {0} ", ptOne - ptTwo);
        // adjust points
        Console.WriteLine("ptOne + delta: {0} ", ptOne + 23);
        Console.WriteLine("ptOne - delta: {0} ", ptOne - 23);
        // freebie += and -=
        Console.WriteLine("ptThree += ptTwo: {0} ", ptThree += ptTwo);
        Console.WriteLine("ptFour  -= ptThree: {0} ", ptFour += ptThree);
        // unaries
        Console.WriteLine("ptOne++: {0} ", ptOne++);
        Console.WriteLine("ptOne--: {0} ", ptOne--);
        Console.WriteLine("++ptOne: {0} ", ++ptOne);
        Console.WriteLine("--ptOne: {0} ", --ptOne);


    }

    public static void TestComplex()
    {
        Complex num1 = new Complex(2,3);
        Complex num2 = new Complex(3,4);

        // Add two Complex objects (num1 and num2) through the
        // overloaded plus operator:
        Complex sum = num1 + num2;

        // Print the numbers and the sum using the overriden ToString method:
        Console.WriteLine("First complex number:  {0}",num1);
        Console.WriteLine("Second complex number: {0}",num2);
        Console.WriteLine("The sum of the two numbers: {0}",sum);       
    }

    public static void Main() 
    {
        TestComplex();
        TestPoint();
    }

}
