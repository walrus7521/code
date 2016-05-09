using System;
using System.IO;
 
public class Logger
{
    private string name;

    // Constructor that takes no arguments.
    public Logger() {
        name = "unknown";
    }

    // Constructor that takes one argument.
    public Logger(string nm) {
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
    static void Main() {
        var log = new Logger("dude");
        string path = "log.txt";
        string res;
        string info = "hey dude wusup";
        log.LogWrite(path, info);
        res = log.LogRead(path);
        Console.WriteLine(res);
    }
}
