using System;

delegate int NumberChanger(int n);

delegate bool CompareInt(int I1, int I2);

namespace DelegateAppl
{
    class TestDelegate1
    {
        static int num = 10;

        // create methods that will be delegated to
        public int AddNum(int p)
        {
            num += p;
            return num;
        }
        public int MultNum(int q)
        {
            num *= q;
            return num;
        }

        public int getNum()
        {
            return num;
        }

        public void TestNumberChanger()
        {
            Console.WriteLine("Testing Number Changer");
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

    }

    class TestDelegate2
    {
        public enum SortType
        {
            Ascending,
            Descending
        }
        // create methods that will be delegated to
        public bool AscendOrder(int I1, int I2)
        {
            if (I1 < I2) {
                Console.WriteLine("Ascending is true");
                return true;
            } else {
                Console.WriteLine("Ascending is false");
                return false;
            }
        }

        public bool DescendOrder(int I1, int I2)
        {
            if (I1 > I2) {
                Console.WriteLine("Descending is true");
                return true;
            } else {
                Console.WriteLine("Descending is false");
                return false;
            }
        }

        public void TestCompareInt(SortType sortDirection, int[] intArray)
        {
            Console.WriteLine("Testing Compare Int");
            CompareInt ci;
            if (sortDirection == SortType.Ascending)
            {
                ci = new CompareInt(AscendOrder);                
            }
            else
            {
                ci = new CompareInt(DescendOrder);
            }
            ci(intArray[0], intArray[1]);
            Console.ReadKey();
        }
    }

    class client
    {
        static void Main(string[] args)
        {
            
            TestDelegate1 td1 = new TestDelegate1();
            td1.TestNumberChanger();
            TestDelegate2 td2 = new TestDelegate2();
            int[] iArray = {3,5,1,3,8};
            
            td2.TestCompareInt(TestDelegate2.SortType.Ascending, iArray);
            td2.TestCompareInt(TestDelegate2.SortType.Descending, iArray);
        }
    }
}

