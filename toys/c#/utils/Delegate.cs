using System;

delegate int NumberChanger(int n);

delegate bool CompareInt(int I1, int I2);

namespace DelegateAppl
{
    class TestDelegate
    {
        static int num = 10;

        // create methods that will be delegated to
        public static int AddNum(int p)
        {
            num += p;
            return num;
        }
        public static int MultNum(int q)
        {
            num *= q;
            return num;
        }

        public static int getNum()
        {
            return num;
        }

        public static TestNumberChanger()
        {

            //create delegate instances
            NumberChanger nc1 = new NumberChanger(AddNum);
            NumberChanger nc2 = new NumberChanger(MultNum);
         
            //calling the methods using the delegate objects
            nc1(25);
            Console.WriteLine("Value of Num: {0}", getNum());
            nc2(5);
            Console.WriteLine("Value of Num: {0}", getNum());
            Console.ReadKey();
        }     

        // create methods that will be delegated to
        public bool AscendOrder(int I1, int I2)
        {

        }

        public bool DescendOrder(int I1, int I2)
        {
        }

        public static TestCompareInt()
        {
        }

        static void Main(string[] args)
        {
            TestNumberChanger();
        }
    }
}

