using System;

// http://www.codeproject.com/Articles/11541/The-Simplest-C-Events-Example-Imaginable
namespace TimerEvents
{
    public class Metronome
    {
        public event TickHandler Tick;
        public EventArgs e = null;
        public delegate void TickHandler(Metronome m, EventArgs e);
        public void Start()
        {
            while (true)
            {
                System.Threading.Thread.Sleep(3000);
                if (Tick != null)
                {
                    Tick(this, e);
                }
            }
        }
    }
    public class Listener
    {
        public void Subscribe(Metronome m)
        {
            m.Tick += new Metronome.TickHandler(HeardIt);
        }
        private void HeardIt(Metronome m, EventArgs e)
        {
            System.Console.WriteLine("HEARD IT");
        }
    }
//    class Test
//    {
//        static void Main()
//        {
//           Metronome m = new Metronome();
//            Listener l = new Listener();
//            l.Subscribe(m);
//            m.Start();
//        }
//    }
}

namespace wildert
{
    public class TimeOfTick : EventArgs
    {
        private DateTime TimeNow;
        public DateTime Time
        {
            get { return this.TimeNow; }
            set { TimeNow = value; }
        }
    }
    public class Clock
    {
        public event TickHandler Tick;
        public delegate void TickHandler(Clock c, TimeOfTick e);
        public void Start()
        {
            while (true)
            {
                System.Threading.Thread.Sleep(1000);
                if (Tick != null)
                {
                    TimeOfTick TOT = new TimeOfTick();
                    TOT.Time = DateTime.Now;
                    Tick(this, TOT);
                }
            }
        }
    }
    public class Metronome
    {
        public event TickHandler Tick;
        public delegate void TickHandler(Metronome m, TimeOfTick e);
        public void Start()
        {
            while (true)
            {
                System.Threading.Thread.Sleep(3000);
                if (Tick != null)
                {
                    TimeOfTick TOT = new TimeOfTick();
                    TOT.Time = DateTime.Now;
                    Tick(this, TOT);
                }
            }
        }
    }
    public class Listener
    {
        private string msg;
        public void Subscribe(Metronome m, string s)
        {
            msg = s;
            m.Tick += new Metronome.TickHandler(HeardIt);
        }
        public void Subscribe2(Clock c, string s)
        {
            msg = s;
            c.Tick += new Clock.TickHandler(HeardIt);
        }

        private void HeardIt(Metronome m, TimeOfTick e)
        {
            System.Console.WriteLine(msg + ": HEARD METRO AT {0}",e.Time);
        }
        private void HeardIt(Clock c, TimeOfTick e)
        {
            System.Console.WriteLine(msg + ": HEARD CLOCK AT {0}",e.Time);
        }

    }
    class Test
    {
        static void Main()
        {
            Metronome m = new Metronome();
            Clock c = new Clock();
            Listener l1 = new Listener();
            Listener l2 = new Listener();
            l1.Subscribe(m, "sup");
            l2.Subscribe(m, "homi");
            m.Start(); // unfortunately these are synchronous
            //c.Start();
        }
    }
}
