using System;
// http://www.dreamincode.net/forums/topic/215620-a-basic-c%23-console-game-movement-engine/
namespace ConsoleGame {
    class Program {
        const ConsoleColor HERO_COLOR = ConsoleColor.DarkBlue;
        const ConsoleColor VILLAIN_COLOR = ConsoleColor.Red;
        const ConsoleColor BACKGROUND_COLOR = ConsoleColor.Green;
        //Will represent our hero that's chasing the villain/>
        public static Coordinate Hero { get; set; } 
        //Will represent our villain that's running away :P/>
        public static Coordinate Villain { get; set; } 
        static void Main(string[] args) {
            InitGame();
            ConsoleKeyInfo keyInfo;
            while ((keyInfo = Console.ReadKey(true)).Key != ConsoleKey.Escape) {
                if (keyInfo.Key.ToString() == "Q") {
                    Console.BackgroundColor = ConsoleColor.Black;
                    Console.Clear(); //Important!
                    Environment.Exit(0);
                }
                if (keyInfo.Key.ToString() == "I") {
                    MoveVillain(0, -1);
                } else
                if (keyInfo.Key.ToString() == "K") {
                    MoveVillain(1, 0);
                } else
                if (keyInfo.Key.ToString() == "M") {
                    MoveVillain(0, 1);
                } else
                if (keyInfo.Key.ToString() == "J") {
                    MoveVillain(-1, 0);
                } else {
                    switch (keyInfo.Key) {
                        case ConsoleKey.UpArrow:
                            MoveHero(0, -1);
                            break;
                        case ConsoleKey.RightArrow:
                            MoveHero(1, 0);
                            break;
                        case ConsoleKey.DownArrow:
                            MoveHero(0, 1);
                            break;
                        case ConsoleKey.LeftArrow:
                            MoveHero(-1, 0);
                            break;
                    }
                }
            }
        }
        /// <summary>
        /// Paint the new hero
        /// </summary>
        static void MoveHero(int x, int y) {
            Coordinate newHero = new Coordinate() {
                X = Hero.X + x,
                Y = Hero.Y + y
            };
            if (CanMove(newHero)) {
                RemoveHero();
                Console.BackgroundColor = HERO_COLOR;
                Console.SetCursorPosition(newHero.X, newHero.Y);
                Console.Write(" ");
                Hero = newHero;
            }
        }
        /// <summary>
        /// Paint the new villain
        /// </summary>
        static void MoveVillain(int x, int y) {
            Coordinate newVillain = new Coordinate() {
                X = Villain.X + x,
                Y = Villain.Y + y
            };
            if (CanMove(newVillain)) {
                RemoveVillain();
                Console.BackgroundColor = VILLAIN_COLOR;
                Console.SetCursorPosition(newVillain.X, newVillain.Y);
                Console.Write(" ");
                Villain = newVillain;
            }
        }
        /// <summary>
        /// Overpaint the old hero
        /// </summary>
        static void RemoveHero() {
            Console.BackgroundColor = BACKGROUND_COLOR;
            Console.SetCursorPosition(Hero.X, Hero.Y);
            Console.Write(" ");
        }
        static void RemoveVillain() {
            Console.BackgroundColor = BACKGROUND_COLOR;
            Console.SetCursorPosition(Villain.X, Villain.Y);
            Console.Write(" ");
        }
        /// <summary>
        /// Make sure that the new coordinate is not placed outside the
        /// console window (since that will cause a runtime crash
        /// </summary>
        static bool CanMove(Coordinate c) {
            if (c.X < 0 || c.X >= Console.WindowWidth)
                return false;
            if (c.Y < 0 || c.Y >= Console.WindowHeight)
                return false;
            return true;
        }
        /// <summary>
        /// Paint a background color
        /// </summary>
        /// <remarks>
        /// It is very important that you run the Clear() method after
        /// changing the background color since this causes a repaint of the background
        /// </remarks>
        static void SetBackgroundColor() {
            Console.BackgroundColor = BACKGROUND_COLOR;
            Console.Clear(); //Important!
        }
        /// <summary>
        /// Initiates the game by painting the background
        /// and initiating the hero
        /// </summary>
        static void InitGame() {
            SetBackgroundColor();
            Hero = new Coordinate() {
                X = 0,
                Y = 0
            };
            MoveHero(0, 0);
            Villain = new Coordinate() {
                X = 4,
                Y = 4
            };
            MoveVillain(0, 0);
        }
    }
    /// <summary>
    /// Represents a map coordinate
    /// </summary>
    class Coordinate {
        public int X { get; set; } //Left
        public int Y { get; set; } //Top
    }
}
