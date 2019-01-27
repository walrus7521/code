import java.io.Console;

class EchoServer
{
    public static void main(String[] args)
    {
        Console console = System.console();
        while (true)
        {
            String msg = console.readLine();
            System.out.println(msg);
        }
    }
}
