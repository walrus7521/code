using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

// mcs /r:Newtonsoft.Json.8.0.3/lib/net40/Newtonsoft.Json.dll Json.cs

// http://stackoverflow.com/questions/13297563/read-and-parse-a-json-file-in-c-sharp
//
// file.json
//[ 
//    { "millis": "1000", 
//      "stamp": "1273010254", 
//      "datetime": "2010/5/4 21:57:34", 
//      "light": "333", 
//      "temp": "78.32", 
//      "vcc": "3.54" 
//    }, 
//    { "millis": "2000", 
//      "stamp": "1273010255", 
//      "datetime": "2010/5/4 21:57:35", 
//      "light": "334", 
//      "temp": "78.34", 
//      "vcc": "3.55" 
//    }, 
//    { "millis": "3000", 
//      "stamp": "1273010256", 
//      "datetime": "2010/5/4 21:57:35", 
//      "light": "335", 
//      "temp": "78.36", 
//      "vcc": "3.56" 
//    }, 
//] 

namespace json
{
    class Program
    {

        public class Item
        {
            public int millis        = 0;
            public string stamp      = null;
            public DateTime datetime = default(DateTime);
            public string light      = null;
            public float temp        = 0.0f;
            public float vcc         = 0.0f;
        }

        public static void LoadJson()
        {
            using (StreamReader r = new StreamReader("file.json"))
            {
                string json = r.ReadToEnd();
                List<Item> items = JsonConvert.DeserializeObject<List<Item>>(json);
                Console.WriteLine("items = {0}", items);
                foreach (var item in items)
                {
                    Console.WriteLine("-> " + item.millis);
                    Console.WriteLine("-> " + item.stamp);
                    Console.WriteLine("-> " + item.datetime);
                    Console.WriteLine("-> " + item.light);
                    Console.WriteLine("-> " + item.temp);
                    Console.WriteLine("-> " + item.vcc);
                }
            }
        }

        static void Main(string[] args)
        {
            LoadJson();
        }
    }
}
