using System;

class DatabaseReader
{
    // Nullable data field
    public int? numericValue = null;
    public bool? boolValue = true;

    // Note the nullable return type
    public int? GetIntFromDatabase()
    {
        return numericValue;
    }

    public bool? GetBoolFromDatabase()
    {
        return boolValue;
    }
}

class Client
{
    public static void Main()
    {
        DatabaseReader dr = new DatabaseReader();

        int? i = dr.GetIntFromDatabase();
        if (i.HasValue)
            Console.WriteLine("Value of 'i' is: {0}", i.Value);
        else
            Console.WriteLine("Value of 'i' is undefined");

        // Get the bool
        bool? b = dr.GetBoolFromDatabase();
        if (b.HasValue)
            Console.WriteLine("Value of 'b' is: {0}", b.Value);
        else
            Console.WriteLine("Value of 'b' is undefined");

        // Now use ?? to suplement null with a default
        // if the value is null
        // assign local variable to 100.
        int myData = dr.GetIntFromDatabase() ?? 100;
        Console.WriteLine("Value of myData: {0}", myData);

        // Long hand notation not using ?? syntax.
        int? moreData = dr.GetIntFromDatabase();
        if (!moreData.HasValue)
            moreData = 100;
        Console.WriteLine("Value of moreData: {0}", moreData);

        Console.ReadLine();
    }
}
