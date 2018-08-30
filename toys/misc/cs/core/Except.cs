using System;
using System.IO;
using System.Collections;

class ExceptOrbital
{
    public void LogOrder(long orderNumber, DateTime orderDate)
    {
        try
        {
            if (orderDate > DateTime.Now)
            {
                throw new ApplicationException("order date can not be in the future.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("LogOrder: exception " + ex.Message);
        }
    }

    public static string ReadText(string filePath)
    {
        StreamReader sr = null;
        try
        {
            sr = File.OpenText(filePath);
            string fileText = sr.ReadToEnd();
            Console.WriteLine("return");
            return fileText;
        }
        catch (DirectoryNotFoundException ex)
        {
            return ex.Message;
        }
        catch (FileNotFoundException ex)
        {
            return ex.Message;
        }
        catch (Exception ex)
        {
            return ex.Message;
        }
        finally
        {
            if (sr != null)
            {
                Console.WriteLine("finally");
                sr.Close();
                sr.Dispose();
            }
        }
    }

    public static void DivByZero()
    {
        int x = 1;
        int y = 0;
        int z = 0;
        try
        {
            try
            {
                z = x / y;
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine("divzero: " + e.Message);
                z = 0;
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("outer: " + e.Message);
        }

        Console.WriteLine("ok z = " + z);
    }

    // custom application exception
    public class CarIsDeadException : ApplicationException
    {
        public DateTime ErrorTimeStamp { get; set; }
        public string CauseOfError { get; set; }

        public CarIsDeadException() {}
        public CarIsDeadException(string message)
            : base(message)
        {
        }
        public CarIsDeadException(string message, string cause, DateTime time)
            : base(message)
        {
            CauseOfError = cause;
            ErrorTimeStamp = time;
        }
        // note you can override Message
        // public override string Message { get { return "yo"; } }
    }

    // awesome custom application exception class
    [Serializable]
    public class CarIsAwesomeException : ApplicationException
    {
        public CarIsAwesomeException(){}
        public CarIsAwesomeException(string message) : base(message) {}
        public CarIsAwesomeException(string message, SystemException inner)
            : base(message, inner) {}
        public CarIsAwesomeException(string message, string cause, DateTime time)
            : base(message)
        {
            CauseOfError = cause;
            ErrorTimeStamp = time;
        }
        protected CarIsAwesomeException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context)
            : base(info, context){}
        // Additional custom properties, constructors and data members...
        public DateTime ErrorTimeStamp { get; set; }
        public string CauseOfError { get; set; }
    }

    public static void TestExcept3()
    {
        throw new ArgumentOutOfRangeException("delta", "Speed up, too slow");

        CarIsAwesomeException ex = 
            new CarIsAwesomeException(string.Format("{0} has overheated!", "Zippy"),
                                   "You have a lead foot.", 
                                   DateTime.Now);
        ex.HelpLink = "http://www.CarsRUs.com";
        ex.Data.Add("item1:", "dude, you need to slow down!!");
        ex.Data.Add("item2:", "so, please use your brakes next time.");
        throw ex;
    }
    
    public static void TestExcept2()
    {
        //CarIsDeadException ex = new CarIsDeadException(string.Format("{0} has overheated!", "Zippy"));
        CarIsDeadException ex = 
            new CarIsDeadException(string.Format("{0} has overheated!", "Zippy"),
                                   "You have a lead foot.", 
                                   DateTime.Now);
        ex.HelpLink = "http://www.CarsRUs.com";
        ex.Data.Add("item1:", "dude, you need to slow down!!");
        ex.Data.Add("item2:", "so, please use your brakes next time.");
        throw ex;
    }

    public static void TestExcept1()
    {
        Exception ex = new Exception(string.Format("{0} has overheated!", "Zippy"));
        ex.HelpLink = "http://www.CarsRUs.com";
        ex.Data.Add("item1:", "dude, you need to slow down!!");
        ex.Data.Add("item2:", "so, please use your brakes next time.");
        throw ex;
    }

    public static void Main()
    {
        //string path = "mutex.cs";
        //string data = ReadText(path);
        //Console.WriteLine(data);
        //DivByZero();
        try 
        {
            //TestExcept1();
            //TestExcept2();
            TestExcept3();
        } 
        catch (ArgumentOutOfRangeException e) 
        {
            Console.WriteLine("ex: ArgumentOutOfRangeException...{0}", e.Message);
        } 
        catch (CarIsAwesomeException e) 
        {
            Console.WriteLine("ex: CarIsAwesomeException...");
            Console.WriteLine("ex: TargetSite               : {0}", e.TargetSite);
            Console.WriteLine("ex: Class defining memger of : {0}", e.TargetSite.DeclaringType);
            Console.WriteLine("ex: Member type              : {0}", e.TargetSite.MemberType);
            Console.WriteLine("ex: Message                  : {0}", e.Message);
            Console.WriteLine("ex: ErrorTimeStamp           : {0}", e.ErrorTimeStamp);
            Console.WriteLine("ex: CauseOfError             : {0}", e.CauseOfError);
            Console.WriteLine("ex: Source                   : {0}", e.Source);
            Console.WriteLine("ex: HelpLink                 : {0}", e.HelpLink);
            Console.WriteLine("ex: StackTrace               :");
            Console.WriteLine(e.StackTrace);

            if (e.Data != null)
            {
                foreach (DictionaryEntry entry in e.Data) {
                    Console.WriteLine(" -> {0}: {1}", entry.Key, entry.Value);
                }
            }
        } 
        catch (CarIsDeadException e) 
        {
            Console.WriteLine("ex: CarIsDeadException...{0}", e.Message);
        } 
        catch (Exception e) 
        {
            Console.WriteLine("ex: Exception...{0}", e.Message);
            throw;
        } 
        catch
        {
            Console.WriteLine("ex: Generic Exception...");
        }
        finally 
        {
            Console.WriteLine("\nokay, move on, nothing to see here...");
        }
    }
}
