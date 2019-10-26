using System;
// http://www.dreamincode.net/forums/topic/215620-a-basic-c%23-console-game-movement-engine/
namespace ConsoleGame {
    class Program {
        const ConsoleColor DARK_BLUE = ConsoleColor.DarkBlue;
        const ConsoleColor RED       = ConsoleColor.Red;
        const ConsoleColor GREEN     = ConsoleColor.Green;
        const ConsoleColor BLACK     = ConsoleColor.Black;
        static void Main(string[] args) {
            Console.BackgroundColor = BLACK;
            Console.ForegroundColor = RED;
            Console.Clear(); //Important!
        }
    }

}
