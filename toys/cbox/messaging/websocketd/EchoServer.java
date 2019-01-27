class EchoServer
{
    static void Main(string[] args)
    {
        while (true)
        {
            var msg = Console.ReadLine();
            Console.WriteLine(msg);
        }
    }
}
