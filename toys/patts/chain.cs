using System;

public interface IEmailHandler
{
    IEmailHandler NextHandler { set; }
    void ProcessHandler(string email);
}

public abstract class AbstractEmailHandler : IEmailHandler
{
    private IEmailHandler nextHandler;
    public virtual IEmailHandler NextHandler {
        set {
            nextHandler = value;
        }
    }

    public virtual void ProcessHandler(string email) {
        bool wordFound = false;
        // if no words to match against then handle it
        if (MatchingWords().Length == 0) {
            wordFound = true;
        } else {
            // look for match
            foreach (string word in MatchingWords()) {
                if (email.IndexOf(word) >= 0) {
                    wordFound = true;
                    break;
                }
            }
        }

        if (wordFound) {
            HandleHere(email);
        } else {
            // chain it
            nextHandler.ProcessHandler(email);
        }
    }

    protected internal abstract string[] MatchingWords();
    protected internal abstract void HandleHere(string email);
}

public class SpamEmailHandler : AbstractEmailHandler
{
    protected internal override string[] MatchingWords() {
        return new string[] {"viagra", "pills", "medicines"};
    }
    protected internal override void HandleHere(string email) {
        Console.WriteLine("This is a spam email");
    }
}

public class SalesEmailHandler : AbstractEmailHandler
{
    protected internal override string[] MatchingWords() {
        return new string[] {"buy", "purchase"};
    }
    protected internal override void HandleHere(string email) {
        Console.WriteLine("This is a sales email");
    }
}

public class ServiceEmailHandler : AbstractEmailHandler
{
    protected internal override string[] MatchingWords() {
        return new string[] {"service", "repair"};
    }
    protected internal override void HandleHere(string email) {
        Console.WriteLine("This is a service email");
    }
}

public class ManagerEmailHandler : AbstractEmailHandler
{
    protected internal override string[] MatchingWords() {
        return new string[] {"complain", "bad"};
    }
    protected internal override void HandleHere(string email) {
        Console.WriteLine("This is a manager email");
    }
}

public class GeneralEnquiriesEmailHandler : AbstractEmailHandler
{
    protected internal override string[] MatchingWords() {
        return new string[0];
    }
    protected internal override void HandleHere(string email) {
        Console.WriteLine("This is a general enquiry email");
    }
}

public class Program
{
    public static void Handle(string email)
    {
        IEmailHandler spam    = new SpamEmailHandler();
        IEmailHandler sales   = new SalesEmailHandler();
        IEmailHandler service = new ServiceEmailHandler();
        IEmailHandler manager = new ManagerEmailHandler();
        IEmailHandler general = new GeneralEnquiriesEmailHandler();

        // chain em
        spam.NextHandler    = sales;
        sales.NextHandler   = service;
        service.NextHandler = manager;
        manager.NextHandler = general;

        spam.ProcessHandler(email);
    }

    public static void Main()
    {
        String email = "I need my car repaired.";
        Handle(email);
    }
}
