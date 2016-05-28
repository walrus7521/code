using System;

public class Car
{
    public int CurrentSpeed {get;set;}
    public int MaxSpeed {get;set;}
    public string PetName {get;set;}
    private bool carIsDead;
    public Car() { MaxSpeed = 100; }
    public Car(string name, int maxSp, int currSp)
    {
        CurrentSpeed = currSp;
        MaxSpeed = maxSp;
        PetName = name;
    }
    // define a delegate type
    public delegate void CarEngineHandler(string msg);
    // define a member variable of this delegate
    private CarEngineHandler listOfHandlers;
    // add a registration function for caller
    public void RegisterWithCarEngine(CarEngineHandler callback)
    {
        listOfHandlers += callback; // allow multi-casting
    }
    public void UnregisterWithCarEngine(CarEngineHandler callback)
    {
        listOfHandlers -= callback; // allow multi-casting
    }
    public void Accelerate(int delta)
    {
        if (carIsDead) {
            if (listOfHandlers != null) {
                listOfHandlers("Sorry, this car is dead...");
            }
        } else {
            CurrentSpeed += delta;
            if (10 == (MaxSpeed - CurrentSpeed)
                    && listOfHandlers != null) {
                listOfHandlers("Careful buddy! Gonna blow!");
            }
            if (CurrentSpeed >= MaxSpeed) {
                carIsDead = true;
            } else {
                Console.WriteLine("CurrentSpeed = {0}", CurrentSpeed);
            }
        }
    }
}


delegate int BinaryOp(int x, int y);
// this class contains methods that
// BinaryOp will point to
public class SimpleMath
{
    public static int Add(int x, int y)
    { return x + y; }
    public static int Sub(int x, int y)
    { return x - y; }
}

delegate int NumberChanger(int n);
class TestDelegate1
{
    static int num = 10;

    // create methods that will be delegated to
    public int AddNum(int p)
    {
        num += p;
        return num;
    }
    public int MultNum(int q)
    {
        num *= q;
        return num;
    }

    public int getNum()
    {
        return num;
    }

    public void TestNumberChanger()
    {
        Console.WriteLine("Testing Number Changer");
        //create delegate instances
        NumberChanger nc1 = new NumberChanger(AddNum);
        NumberChanger nc2 = new NumberChanger(MultNum);
     
        //calling the methods using the delegate objects
        nc1(25);
        Console.WriteLine("Value of Num: {0}", getNum());
        nc2(5);
        Console.WriteLine("Value of Num: {0}", getNum());
        Console.ReadKey();
    }     

}

delegate bool CompareInt(int I1, int I2);
class TestDelegate2
{
    public enum SortType
    {
        Ascending,
        Descending
    }
    // create methods that will be delegated to
    public bool AscendOrder(int I1, int I2)
    {
        if (I1 < I2) {
            Console.WriteLine("Ascending is true");
            return true;
        } else {
            Console.WriteLine("Ascending is false");
            return false;
        }
    }

    public bool DescendOrder(int I1, int I2)
    {
        if (I1 > I2) {
            Console.WriteLine("Descending is true");
            return true;
        } else {
            Console.WriteLine("Descending is false");
            return false;
        }
    }

    public void TestCompareInt(SortType sortDirection, int[] intArray)
    {
        Console.WriteLine("Testing Compare Int");
        CompareInt ci;
        if (sortDirection == SortType.Ascending)
        {
            ci = new CompareInt(AscendOrder);                
        }
        else
        {
            ci = new CompareInt(DescendOrder);
        }
        ci(intArray[0], intArray[1]);
        Console.ReadKey();
    }
}

class client
{

    static void TestCar()
    {
        Car c1 = new Car("SlugBug", 100, 10);
        c1.RegisterWithCarEngine(new Car.CarEngineHandler(OnCarEngineEvent));
        //Car.CarEngineHandler h2 = new Car.CarEngineHandler(OnCarDupEvent);
        //c1.RegisterWithCarEngine(h2);
        //c1.UnregisterWithCarEngine(h2);
        // alternate syntactic sugar
        c1.RegisterWithCarEngine(OnCarTripleEvent);
        //c1.UnregisterWithCarEngine(OnCarTripleEvent);

        Console.WriteLine("speed up..");
        for (int i = 0; i < 6; i++) {
            c1.Accelerate(20);
        }
        Console.ReadLine();
    }

    public static void OnCarEngineEvent(string msg)
    {
        Console.WriteLine("*** Message from Car Object ***");
        Console.WriteLine("=> {0} ", msg);
        Console.WriteLine("*******************************");
    }

    public static void OnCarDupEvent(string msg)
    {
        Console.WriteLine("*** Duplicate Message from Car Object ***");
    }

    public static void OnCarTripleEvent(string msg)
    {
        Console.WriteLine("*** Triple Message from Car Object ***");
    }

    static void DisplayDelegateInfo(Delegate delObj)
    {
        // print names of each member
        foreach (Delegate d in delObj.GetInvocationList())
        {
            Console.WriteLine("Method Name: {0}", d.Method);
            Console.WriteLine("Type Name:   {0}", d.Target);
        }
    }

    static void TestMath()
    {
        Console.WriteLine("Test Math...");
        BinaryOp add = new BinaryOp(SimpleMath.Add);
        BinaryOp sub = new BinaryOp(SimpleMath.Sub);
        Console.WriteLine("1+1={0}", add(1,1));
        Console.WriteLine("2-1={0}", sub(2,1));
        // let's display the delegate info
        DisplayDelegateInfo(add);
        DisplayDelegateInfo(sub);
    }

    static void Main(string[] args)
    {
        TestCar();
        
        TestMath();

        TestDelegate1 td1 = new TestDelegate1();
        td1.TestNumberChanger();
        TestDelegate2 td2 = new TestDelegate2();
        int[] iArray = {3,5,1,3,8};
            
        td2.TestCompareInt(TestDelegate2.SortType.Ascending, iArray);
        td2.TestCompareInt(TestDelegate2.SortType.Descending, iArray);
    }
}
