using System;
using System.Collections;
using System.Collections.Generic;

// mcs ClientAdapter.cs AbstractFactory2.cs Adapter.cs

namespace MyClient
{
    public class Client
    {
        public static void Main()
        {
            IList<IEngine> engines = new List<IEngine>();

            engines.Add(new StandardEngine(1300));
            engines.Add(new StandardEngine(1600));
            engines.Add(new TurboEngine(2000));

            // Adapt the new engine type
            SuperGreenEngine greenEngine = new SuperGreenEngine(1200);
            engines.Add(new SuperGreenEngineAdapter(greenEngine));

            foreach (var engine in engines)
            {
                Console.WriteLine(engine);
            }
            Console.Read();
        }
    }
}
