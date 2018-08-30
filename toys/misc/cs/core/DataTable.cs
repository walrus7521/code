using System;
using System.Data;
using System.Collections;
using System.Collections.Generic;
using System.Web;
//using System.Web.Script.Serialization;

// mcs /r:System.Data.dll DataTable.cs

class Client
{

    //public static string DataTableToJSON(DataTable table)
    //{
    //    var list = new List<Dictionary<string, object>>();
    //    foreach (DataRow row in table.Rows) {
    //        var dict = new Dictionary<string, object>();
    //        foreach (DataColumn col in table.Columns) {
    //            dict[col.ColumnName] = row[col];
    //        }
    //        list.Add(dict);
    //    }
    //    JavaScriptSerializer serializer = new JavaScriptSerializer();
    //    return serializer.Serialize(list);
    //}


    static void MultiIndexerWithDataTable()
    {
        // simple DataTable with 3 columns
        DataTable table = new DataTable();
        table.Columns.Add("first");
        table.Columns.Add("last");
        table.Columns.Add("age");

        table.Rows.Add("bart", "bartel", 57);
        
        Console.WriteLine("first {0}", table.Rows[0][0]);
        Console.WriteLine("last  {0}", table.Rows[0][1]);
        Console.WriteLine("age   {0}", table.Rows[0][2]);
    }

    public static void Main()
    {
        MultiIndexerWithDataTable();
    }
}
