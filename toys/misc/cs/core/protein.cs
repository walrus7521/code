using System;
using System.Net;
using System.Text;
using System.Threading.Tasks;

// efetch.fcgi?rettype=fasta retmode=text db=protein&id=P01308
//
class Client
{
    public static string NcbiEntrez(string query)
    {
        byte[] bytes = new WebClient().DownloadData(new Uri("http://www.ncbi.nlm.nih.gov/entrez/eutils/" + query));
        return ASCIIEncoding.ASCII.GetString(bytes);
    }

    public static string NcbiProtein(string id)
    {
        return NcbiEntrez("efetch.fcgi?rettype=fasta&retmode=text&db=protein&id=" + id);
    }

    public static string[] NcbiProteinParallel(params string[] ids)
    {
        string[] results = new string[ids.Length];
        Parallel.For(0, ids.Length, i => { results[i] = NcbiProtein(ids[i]); });
        return results;
    }

    public static void Main()
    {
        string prot = NcbiProtein("P01308");
        Console.WriteLine("protein = " + prot);
        string[] prots = NcbiProteinParallel("P01308", "P01315", "P01317");
        foreach (var s in prots)
        {
            Console.WriteLine("prot: " + s);
        }
    }
}


