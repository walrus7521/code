using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Reflection;
using System.IO;

// csc -target:library Dynamics.cs


namespace DynamicsUtils
{
    public class SimpleMath
    {
        public int Add(int x, int y)
        {
            return (x + y);
        }
    }


}
