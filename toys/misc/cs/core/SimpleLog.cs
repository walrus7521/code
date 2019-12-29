using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
 
namespace Logger {
public class Log : IEnumerable<string> {
    private static readonly int SIZE = 256;
    private static int instanceCount = 0;
    private int count = 0;
    private string _filename;
    private System.IO.StreamWriter file;
    private string[] log = new string[SIZE];
    public Log(string filename) { 
        _filename = filename;
        file = new System.IO.StreamWriter(filename, true);
        instanceCount++; 
    }
    ~Log() {
        file.Close();
    }
    public static int InstanceCount { get { return instanceCount; }}
    public void Add(string msg) { 
        log[count++ % SIZE] = msg;  // circular buffer
        // Write the string to a file.append mode is enabled so that the log
        // lines get appended to  test.txt than wiping content and writing the log
        file.WriteLine(msg);
    }
    public int Count { get { return count; }}
    public string Last {
        get {
            return count == 0 ? null : log[(count-1)%SIZE];
        }
        set {
            if (count == 0) {
                log[count++] = value;
            } else {
                log[(count-1)%SIZE] = value;
            }
        }
    }
    public string this[int i] {
        get {
            return log[(i)%SIZE];
        }
    }
    public IEnumerator<string> GetEnumerator() {
        for (int i = 0; i < count; i++) {
            yield return log[i];
        }
    }
    IEnumerator IEnumerable.GetEnumerator() {
        return GetEnumerator();
    }    
}
}

class TestLogger
{
    static void Test()
    {
        Logger.Log log = new Log("test.log");
        log.Add("hey");
        log.Add("sup");
        log.Add("homi");
        log.Add("dude");
        Console.WriteLine("last: " + log.Last);
        for (int i = 0; i < log.Count; i++) {
            Console.WriteLine("get: " + log[i]);
        }
        foreach (var s in log)
        {
            Console.WriteLine("get: " + s);
        }
    }

    static void Main() {
        Test();
    }
}

