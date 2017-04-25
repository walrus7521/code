using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// mcs -target:library ch14CarLib.cs ch14CarDerived.cs
// instead of ildasm.exe, in mono use monodis <assembly>

namespace CarLibrary
{
    public enum EngineState
    { engineAlive, engineDead }
    public enum MusicMedia
    {
        musicCd,    // 0
        musicTape,  // 1
        musicRadio, // 2
        musicMp3    // 3

    }
    public abstract class Car
    {
        public string PetName {get;set;}
        public int CurrentSpeed {get;set;}
        public int MaxSpeed {get;set;}

        protected EngineState egnState = EngineState.engineAlive;
        public EngineState EngineState { get{ return egnState; }}

        public abstract void TurboBoost();
        public void TurnOnRadio(bool musicOn, MusicMedia mm) {
            if (musicOn) {
                Console.WriteLine(string.Format("Jamming {0}", mm));
            } else {
                Console.WriteLine("Quiet time...");
            }
        }

        public Car(){}
        public Car(string name, int maxSp, int currSp)
        { PetName = name; MaxSpeed = maxSp; CurrentSpeed = currSp; }

    }
}
