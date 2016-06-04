using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// mcs -target:library ch14CarLib.cs ch14CarDerived.cs
// you can optionally make an exe and still reference the assembly!! sweet!!
// instead of ildasm.exe, in mono use monodis <assembly>

namespace CarLibrary
{
    public class SportsCar : Car
    {
        public SportsCar(){}
        public SportsCar(string name, int maxSp, int currSp)
            : base(name, maxSp, currSp) {}
        public override void TurboBoost()
        {
            Console.WriteLine("Ramming speed!", "Faster is better...");
        }
    }

    public class MiniVan : Car
    {
        public MiniVan(){}
        public MiniVan(string name, int maxSp, int currSp)
            : base(name, maxSp, currSp) {}
        public override void TurboBoost()
        {
            egnState = EngineState.engineDead;
            Console.WriteLine("Eek!", "Your engine block is exploded...");
        }
    }
}

public class Client
{
    static void Main(){}
}
