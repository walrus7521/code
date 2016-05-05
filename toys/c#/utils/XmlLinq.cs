using System;
using System.Xml;
using System.Xml.Linq;

class XmlLinq
{
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
    }
}
