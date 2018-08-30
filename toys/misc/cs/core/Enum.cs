using System;
using System.Collections;

public class Car
{
    public Car(){}
    public Car(string name, int speed)
    {
        PetName = name;
        CurrentSpeed = speed;
    }
    public string PetName { get; set; }
    public int CurrentSpeed { get; set; }
}

public class Garage : IEnumerable
{
    private Car[] carArray = new Car[4];
    public Garage()
    {
        carArray[0] = new Car("Rusty", 30);
        carArray[1] = new Car("Clunker", 55);
        carArray[2] = new Car("Zippy", 30);
        carArray[3] = new Car("Fred", 30);
    }
    // we can implement this one
    //public IEnumerator GetEnumerator()
    //{
    //    // return the array object's IEnumerator
    //    return carArray.GetEnumerator();
    //}
    // or this one
    public IEnumerator GetEnumerator()
    {
        // return the array object's IEnumerator
        foreach (Car c in carArray) {
            yield return c;
        }
    }

    public IEnumerable GetTheCars(bool ReturnReversed)
    {
        if (ReturnReversed)
        {
            for (int i = carArray.Length; i != 0; i--) {
                yield return carArray[i-1];
            }
        } else {
            foreach (Car c in carArray) {
                yield return c;
            }
        }
    }
}

public class Program
{
    public static void Version1()
    {
        Garage carLot = new Garage();
        foreach (Car c in carLot) {
            Console.WriteLine("{0} is going {1} MPH",
                    c.PetName, c.CurrentSpeed);
        }
        // manual way
        IEnumerator i = carLot.GetEnumerator();
        i.MoveNext();
        Car myCar = (Car) i.Current;
        Console.WriteLine("::=> {0} is going {1} MPH", myCar.PetName, myCar.CurrentSpeed);
        Console.WriteLine("Get the cars in reverse");
        foreach (Car c in carLot.GetTheCars(true)) {
            Console.WriteLine("{0} is going {1} MPH",
                    c.PetName, c.CurrentSpeed);

        }
    }

    public static void Main()
    {
        Version1();
    }
}
