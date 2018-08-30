using System;
using System.Xml;
using System.Linq;
using System.Xml.Linq;
using System.Collections;
using System.Collections.Generic;

class XmlLinq
{
    private static void XmlToDict()
    {       
        XElement root = new XElement("Root",
            new XElement("Child1", "Value1"),
            new XElement("Child2", "Value2"),
            new XElement("Child3", "Value3"),
            new XElement("Child4", "Value4")
        );

        Dictionary<string, string> dict = new Dictionary<string, string>();
        foreach (XElement el in root.Elements())
            dict.Add(el.Name.LocalName, el.Value);
        foreach (string str in dict.Keys)
            Console.WriteLine("{0}:{1}", str, dict[str]);        
    }

    private static void DictToXml()
    {       
        Dictionary<string, string> dict = new Dictionary<string, string>();
        dict.Add("Child1", "Value1");
        dict.Add("Child2", "Value2");
        dict.Add("Child3", "Value3");
        dict.Add("Child4", "Value4");
        XElement root = new XElement("Root",
            from keyValue in dict
            select new XElement(keyValue.Key, keyValue.Value)
        );
        Console.WriteLine(root);
    }

    private static void BuildXmlDocWithLINQToXml()
    {
        XElement doc =
            new XElement("Inventory",
                    new XElement("Car", new XAttribute("ID", "1000"),
                        new XElement("PetName", "Jimbo"),
                        new XElement("Color", "Red"),
                        new XElement("Make", "Ford")
                        )
                    );
        doc.Save("InventoryWithLINQ.xml");
    }

    private static void Main()
    {
        BuildXmlDocWithLINQToXml();
        XmlToDict();
        DictToXml();
    }
}

