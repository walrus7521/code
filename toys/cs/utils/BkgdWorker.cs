using System;
using System.Collections;
using System.ComponentModel;
using System.Threading;

class Program
{
    private static BackgroundWorker worker = new BackgroundWorker();
    private event EventHandler BackgroundWorkFinished;
 
    static void worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
    {
        Console.WriteLine(e.ProgressPercentage.ToString());
    }
 
    static void worker_DoWork(object sender, DoWorkEventArgs e)
    {
        Console.WriteLine("Starting to do some work now...");
        int i;
        for (i = 1; i < 10; i++)
        {
            Thread.Sleep(1000);
            worker.ReportProgress(Convert.ToInt32((100.0 * i) / 10));
        }
 
        e.Result = i;
    }
 
    static void worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
        Console.WriteLine("Value Of i = " + e.Result.ToString());
        Console.WriteLine("Done now...");
    }

    static void Main(string[] args)
    {
        worker.DoWork += worker_DoWork;
        worker.RunWorkerCompleted += worker_RunWorkerCompleted;
        worker.ProgressChanged += worker_ProgressChanged;
        worker.WorkerReportsProgress = true;
        worker.WorkerSupportsCancellation = true;
 
        Console.WriteLine("Starting Application...");
 
        worker.RunWorkerAsync();
        Console.ReadKey();
    }
 
}
