using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
 
public class Log {
    private static readonly int SIZE = 256;
    private static int instanceCount = 0;
    private int count = 0;
    private string[] log = new string[SIZE];
    public Log() { instanceCount++; }
    public static int InstanceCount { get { return instanceCount; }}
    public void Add(string msg) { log[count++ % SIZE] = msg; }
    public int Count { get { return count; }}
    public string Last {
        get
        {
            return count == 0 ? null : log[(count-1)%SIZE];
        }
        set
        {
            if (count == 0)
            {
                log[count++] = value;
            }
            else
            {
                log[(count-1)%SIZE] = value;
            }
        }
    }
    public string this[int i]
    {
        get
        {
            return log[(i)%SIZE];
        }
    }
    //public string[] All { ... }
}


public class Logger
{
    private List<string> log;
    public Logger()
    {
        log = new List<string>();
    }
    public void add(string msg)
    {
        log.Add(msg);
    }

    public void show()
    {
        foreach (var m in this.log)
        {
            Console.WriteLine(m);
        }
    }
}

public class Logger2
{
    private string name;

    // Constructor that takes no arguments.
    public Logger2() {
        name = "unknown";
    }

    // Constructor that takes one argument.
    public Logger2(string nm) {
        name = nm;
    }
    
    public string LogRead(string filePath) {
        StreamReader sr = null;
        string fileText;
        try {
            sr = File.OpenText(filePath);
            fileText = sr.ReadToEnd();
            return fileText;
        } catch (DirectoryNotFoundException ex) {
            return ex.Message;
        } catch (FileNotFoundException ex) {
            return ex.Message;
        } catch (IOException ex) {
            return ex.Message;
        } catch {
            return "Logging failed";
        } finally {
            if (sr != null) {
                sr.Close();
                sr.Dispose();
            }
        }
    }

    public string LogWrite(string logPath, string logInfo) {
        StreamWriter sw = null;
        try {
            FileStream oFileStream = new FileStream(logPath, FileMode.Open,
                    FileAccess.Write);
            sw = new StreamWriter(oFileStream);
            oFileStream.Seek(0, SeekOrigin.End);
            sw.WriteLine(DateTime.Now);
            sw.WriteLine(logInfo);
            sw.WriteLine();
            sw.Close();
            return "Logging succeeded";
        } catch (DirectoryNotFoundException ex) {
            return ex.Message;
        } catch (FileNotFoundException ex) {
            return ex.Message;
        } catch (IOException ex) {
            return ex.Message;
        } catch {
            return "Logging failed";
        } finally {
            if (sw != null) {
                sw.Close();
                sw.Dispose();
            }
        }
    }
}

class TestLogger
{
    static void Test1()
    {
        var log = new Logger2("dude");
        string path = "log.txt";
        string res;
        string info = "hey dude wusup";
        log.LogWrite(path, info);
        res = log.LogRead(path);
        Console.WriteLine(res);
    }

    static void Test2()
    {
        var log = new Logger();
        log.add("hello");
        log.add("there");
        log.show();

    }

    static void Test3()
    {
        Log log = new Log();
        log.Add("hey");
        log.Add("sup");
        log.Add("homi");
        log.Add("dude");
        Console.WriteLine("last: " + log.Last);
        for (int i = 0; i < log.Count; i++) {
            Console.WriteLine("get: " + log[i]);
        }
        //foreach (var s in log)
        //{
        //    Console.WriteLine("get: " + s);
        //}
    }

    static void Main() {
        Test3();
    }
}
