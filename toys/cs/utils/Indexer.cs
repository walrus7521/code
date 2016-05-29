using System;
using System.Collections;

public class CustomCollection : IEnumerable
{
    private ArrayList ccList = new ArrayList();
    public void Add(object o) {
        ccList.Add(o);
    }
    public object Get(int idx) {
        return ccList[idx];
    }
    public void Clear() {
        ccList.Clear();
    }
    // create an custom indexer for this class
    public object this[int index] {
        get { return ccList[index]; }
        set { ccList.Insert(index, value); }
    }
    // create an enumerator for foreach
    IEnumerator IEnumerable.GetEnumerator() {
        return ccList.GetEnumerator();
    }
} 

public class client
{
    public static void Main()
    {
        CustomCollection cc = new CustomCollection();
        for (int i = 0; i < 4; i++) {
            object o = i;
            cc.Add(o);
        }
        for (int i = 0; i < 4; i++) {
            object o = cc[i]; // use indexer -- way cool!!
            Console.WriteLine("index[{0}]: {1}", i, o);
        }
        foreach (var j in cc) { // use IEnumerable
            Console.WriteLine("j = {0}", j);
        }
        for (int i = 0; i < 4; i++) { // use getter
            object o = cc.Get(i);
            Console.WriteLine("got: {0}", o);
        }
        cc.Clear();
    }
}
