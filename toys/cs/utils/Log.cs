using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
 
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

    static void Main() {
        Test2();
    }
}
