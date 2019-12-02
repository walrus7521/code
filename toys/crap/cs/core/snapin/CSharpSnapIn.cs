using System;
using System.Collections;
using System.Linq;
using System.Text;

using CommonSnappableTypes;
using System.Windows.Forms;

// build using:
// csc /target:library CSharpSnapIn.cs /r:CommonSnappableTypes.dll
//
namespace CSharpSnapIn
{

    [CompanyInfo(CompanyName = "Bartco",
        CompanyUrl = "www.bartco.com")]
    public class CSharpModule : IAppFunctionality
    {
        void IAppFunctionality.DoIt()
        {
            Console.WriteLine("You have just used the C# snap-in!");
        }
    }
}
