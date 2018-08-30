using System;

namespace TestEvents
{
    public class MyEvents
    {
        public delegate void DataUpdateEventHandler(string msg); // signature
        public event DataUpdateEventHandler DataUpdate; // event
        private void DoThis(string m) // actual event handler
        {
            Console.WriteLine("dude: " + m);
        }
        public MyEvents()
        {
            DataUpdate += new DataUpdateEventHandler(DoThis); // register the event handler
        }

        public void SaveInfo()
        {
            try
            {
                DataUpdate("Data has been updated"); // pulse the event
            }
            catch
            {
                DataUpdate("Data could not be updated"); // pulse the event
            }
        }
    }
   class Test
    {
        public static event MyEvents.DataUpdateEventHandler DataUpdate2; // event
        static void DoThat(string m) // actual event handler
        {
            Console.WriteLine("wusup: " + m);
        }
        
        static void Main()
        {
            MyEvents ev1 = new MyEvents();
            ev1.SaveInfo();

            MyEvents ev2 = new MyEvents();
            DataUpdate2 += new MyEvents.DataUpdateEventHandler(DoThat); // register the event handler
            DataUpdate2("yo homi");

        }
    }
}
