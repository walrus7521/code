using System;
using System.Collections;

public class Car : IComparable
{
    public Car(){}
    public Car(string name, int speed, int id)
    {
        PetName = name;
        CurrentSpeed = speed;
        CarID = id;
    }
    public string PetName { get; set; }
    public int CurrentSpeed { get; set; }
    public int CarID {get;set;}

    // this way
    int IComparable.CompareTo(object obj)
    {
        Car temp = obj as Car;
        if (temp != null)
            return this.CarID.CompareTo(temp.CarID);
        else
            throw new ArgumentException("Parameter is not a Car!");
    }
    // or this
    //int IComparable.CompareTo(object obj)
    //{
    //    Car temp = obj as Car;
    //    if (temp != null)
    //    {
    //        if (this.CarID > temp.CarID) {
    //            return 1;
    //        }
    //        else if (this.CarID < temp.CarID) {
    //            return -1;
    //        }
    //        else {
    //            return 0;
    //        }
    //    } else {
    //        throw new ArgumentException("Parameter is not a Car!");
    //    }
    //}

    // add static member to assist users in sorting
    public static IComparer SortByPetName
    { get { return (IComparer) new PetNameComparer(); } }
}

// now lets make a class that can be sorted by 2 items: ID and PetName
public class PetNameComparer : IComparer
{
    int IComparer.Compare(object o1, object o2)
    {
        Car t1 = o1 as Car;
        Car t2 = o2 as Car;
        if (t1 != null && t2 != null)
            return String.Compare(t1.PetName, t2.PetName);
        else
            throw new ArgumentException("Parameter is not a Car!");
    }
} 

public class Program
{
    public static void Version1()
    {
        Car[] myAutos = new Car[5];
        myAutos[0] = new Car("Rusty",  80,   1);
        myAutos[1] = new Car("Mary",   40, 234);
        myAutos[2] = new Car("Viper",  40,  34);
        myAutos[3] = new Car("Mel",    40,   4);
        myAutos[4] = new Car("Chucky", 40,   5);
        Console.WriteLine("unsorted...");
        foreach (Car c in myAutos) {
            Console.WriteLine("{0}\t{1}", c.CarID, c.PetName);
        }
        Console.WriteLine("sorted by ID...");
        Array.Sort(myAutos);
        foreach (Car c in myAutos) {
            Console.WriteLine("{0}\t{1}", c.CarID, c.PetName);
        }
        Console.WriteLine("sorted by PetName...");
        //Array.Sort(myAutos, new PetNameComparer());
        Array.Sort(myAutos, Car.SortByPetName);
        foreach (Car c in myAutos) {
            Console.WriteLine("{0}\t{1}", c.PetName, c.CarID);
        }
    }

    public static void Main()
    {
        Version1();
    }
}
