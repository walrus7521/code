using System;
using System.Xml;

public class Client
{
    public static void Write()
    {
        XmlTextWriter writer = new XmlTextWriter(Console.Out);
        writer.WriteStartDocument();
        writer.WriteElementString("Hello", "Xml");
        writer.WriteEndDocument();
        writer.Close();
    }

    public static void Read()
    {
        XmlTextReader reader = new XmlTextReader("books.xml");
        while (reader.Read()) 
        {
            switch (reader.NodeType) 
            {
                case XmlNodeType.Element: // The node is an element.
                    Console.Write("<" + reader.Name);
                    while (reader.MoveToNextAttribute()) // Read the attributes.
                        Console.Write(" " + reader.Name + "='" + reader.Value + "'");
                    Console.WriteLine(">");
                    break;
                case XmlNodeType.Text: //Display the text in each element.
                    Console.WriteLine (reader.Value);
                    break;
                case XmlNodeType. EndElement: //Display the end of the element.
                    Console.Write("</" + reader.Name);
                    Console.WriteLine(">");
                break;
            }
        }
        // Do some work here on the data.
        Console.ReadLine();        
    }

    public static void Main()
    {
        //Write();
        Read(); // books.xml
    }
}
