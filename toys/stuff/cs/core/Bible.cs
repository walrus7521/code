using System;
using System.IO;
using System.Collections.Generic;

public class Bible
{

    public static string[] SplitLine(string line)
    {
        string[] result;
        //string[] separators = new string[] {" "};
        string[] separators = {",", ".", "!", "?", ";", ":", " "};
        result = line.Split(separators, StringSplitOptions.None);
        return result;
    }

    public static Dictionary<string, int> ReplaceFile(string FilePath, string NewFilePath)
    {
       Dictionary<string, int> word_freq = new Dictionary<string, int>();
       using (StreamReader vReader = new StreamReader(FilePath))
       {
          using (StreamWriter vWriter = new StreamWriter(NewFilePath))
          {
             int vLineNumber = 0;
             while (!vReader.EndOfStream)
             {
                string vLine = vReader.ReadLine();
                string[] words = SplitLine(vLine);
                foreach (string s in words) {
                    try {
                        word_freq[s]++;
                        //Console.WriteLine("=> {0}", s);
                    } catch (Exception ex) {
                        word_freq[s] = 1;
                    }
                }
                vWriter.WriteLine(ReplaceLine(vLine, vLineNumber++));
             }
          }
       }
       return word_freq;
    }
    public static string ReplaceLine(string Line, int LineNumber )
    {
       //Do your string replacement and 
       //return either the original string or the modified one
       return Line;
    }

    static void Main()
    {
        Dictionary<string, int> wf = ReplaceFile("bible.txt", "word.txt");
        //foreach(var item in wf) {
        //    Console.WriteLine("{0} => {1}", item.Key, item.Value);
        //}
        Console.WriteLine("God: {0}", wf["God"]);
        Console.WriteLine("Jesus: {0}", wf["Jesus"]);
        Console.WriteLine("Grace: {0}", wf["Grace"]);
        Console.WriteLine("grace: {0}", wf["grace"]);

    }
}
