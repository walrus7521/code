using System;
using System.Xml;

public class Client
{
    public static void Main()
    {
        XmlTextWriter writer = new XmlTextWriter(Console.Out);
        writer.WriteStartDocument();
        writer.WriteElementString("Hello", "Xml");
        writer.WriteEndDocument();
        writer.Close();
    }
}
