using System;
using System.Collections;
using System.Collections.Generic;

public class CustomCollection : IEnumerable
{
    private ArrayList aList = new ArrayList();
    public void Add(int i) {
        aList.Add(i.ToString());
    }
    public string Get(int idx) {
        return (string) aList[idx];
    }
    public void Clear() {
        aList.Clear();
    }
    // create an custom indexer for this class
    public string this[string str_index] {
        get { return (string) aList[Int32.Parse(str_index)]; }
        set { aList.Insert(Int32.Parse(str_index), value); }
    }
     public string this[int index] {
        get { return (string) aList[index]; }
        set { aList.Insert(index, value); }
    }
    // create an enumerator for foreach
    IEnumerator IEnumerable.GetEnumerator() {
        return aList.GetEnumerator();
    }
} 

public class CustomCollection2 : IEnumerable
{
    private Dictionary<string, int> dList = new Dictionary<string, int>();
    public void Add(string s, int i) {
        dList[s] = i;
    }
    public int Get(string s) {
        return dList[s];
    }
    public void Clear() {
        dList.Clear();
    }
    // create an custom indexer for this class
    public int this[string s] {
        get { return dList[s]; }
        set { dList[s] = value; }
    }
    // create an enumerator for foreach
    IEnumerator IEnumerable.GetEnumerator() {
        return dList.GetEnumerator();
    }
} 

public class CustomCollection3
{
    private int[,] TwoDArray = new int[10,10];
    // create an custom indexer for this class
    public int this[int row, int column] {
        get { return TwoDArray[row, column]; }
        set { TwoDArray[row, column] = value; }
    }
} 

public interface IStringContainer
{
    string this[int index] { get; set; }
}

public class CustomClass : IStringContainer
{
    private List<string> myStrings = new List<string>();

    public string this[int index]
    {
        get { return myStrings[index]; }
        set { myStrings.Insert(index, value); }
    }
}

public class client
{
    public static void TestCC1()
    {
        Console.WriteLine("Test CC1");
        CustomCollection cc = new CustomCollection();
        for (int i = 0; i < 4; i++) {
            cc.Add(i);
        }
        for (int i = 0; i < 4; i++) {
            int o = Int32.Parse(cc[i]); // use indexer -- way cool!!
            Console.WriteLine("index[{0}]: {1}", i, o);
        }
        foreach (var j in cc) { // use IEnumerable
            Console.WriteLine("j = {0}", j);
        }
        for (int i = 0; i < 4; i++) { // use getter
            int o = Int32.Parse(cc.Get(i));
            Console.WriteLine("got: {0}", o);
        }
        cc.Clear();
     }

    public static void TestCC2()
    {
        Console.WriteLine("Test CC2");
        CustomCollection2 cc = new CustomCollection2();
        for (int i = 0; i < 4; i++) {
            cc.Add(i.ToString(), i);
        }
        for (int i = 0; i < 4; i++) {
            int o = cc[i.ToString()]; // use indexer -- way cool!!
            Console.WriteLine("index[{0}]: {1}", i, o);
        }
        foreach (var j in cc) { // use IEnumerable
            Console.WriteLine("j = {0}", j);
        }
        for (int i = 0; i < 4; i++) { // use getter
            int o = cc.Get(i.ToString());
            Console.WriteLine("got: {0}", o);
        }
        cc.Clear();
    }

    public static void TestCC3()
    {
        Console.WriteLine("Test CC3");
        CustomCollection3 cc = new CustomCollection3();
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                cc[row,col] = row*col;
            }
        }
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                Console.WriteLine("cc[{0},{1}] = {2}", row, col, cc[row,col]);
            }
        }
    }

    public static void TestCC4()
    {
        Console.WriteLine("Test CC4");
        CustomClass cc = new CustomClass();
        cc[0] = "bart";
        cc[1] = "grant";
        cc[2] = "chad";
        Console.WriteLine("cc[{0}] = {1}", 0, cc[0]);
        Console.WriteLine("cc[{0}] = {1}", 1, cc[1]);
        Console.WriteLine("cc[{0}] = {1}", 2, cc[2]);
    }

    public static void Main()
    {
        TestCC1();
        TestCC2();
        TestCC3();
        TestCC4();
    }
}
