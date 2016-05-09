using System;
using System.Collections;
using System.Collections.Generic;

// using interfaces
// interfaces force the contract
// note: .NET does not allow multiple intheritance
// but a class can implement multiple interfaces
public interface IAccount
{
    string GetAccountInfo();
}

public class XCheckingAccount : IAccount
{
    public string GetAccountInfo()
    {
        return "XCheckingAccount: Printing checking account info";
    }
}

sealed class XSavingsAccount : IAccount
{
    public string GetAccountInfo()
    {
        return "XSavingsAccount: Printing checking account info";
    }
}

// using abstract base class
public abstract class Account
{
    int _accountNumber;

    public abstract string GetAccountInfo();

    public virtual void Peek()
    {
        Console.WriteLine("Account::Peek");
    }
    protected double GetBalance(int accountNumber)
    {
        _accountNumber = accountNumber;
        if (_accountNumber == 1) 
        {
            return 1000;
        }
        else if (_accountNumber == 2)
        {
            return 2000;
        }
        else
        {
            throw new Exception("Account number is incorrect.");
        }
    }

    public abstract void Deposit(double amount); // must be overriden
    // OR
    //public virtual void Deposit(double amount)
    //{
    //    // default base class code
    //}

}

class CheckingAccount : Account
{
    private double _balance = 2000;

    public override string GetAccountInfo()
    {
        return "CheckingAccount: Printing account info";
    }
    public override void Peek()
    {
        base.Peek();
        Console.WriteLine("CheckingAccount::Peek");
    }
    public void Peek(int account)
    {
        base.Peek();
        Console.WriteLine("CheckingAccount::Peek: " + account);
    }
    public virtual void HideMe()
    {
        Console.WriteLine("CheckingAccount::HideMe");
    }
    public double Balance
    {
        get { return _balance; }
    }
    public virtual double GetMinBalance()
    {
        Console.WriteLine("CheckingAccount::GetMinBalance");
        return 200;
    }
    public virtual void Withdraw(double amount)
    {
        double minBalance = GetMinBalance();
        if (minBalance < (Balance - amount))
        {
            _balance -= amount;
        }
        else
        {
            throw new Exception("Minimum balance error.");
        }
    }

    // override if base class method is abstract
    public override void Deposit(double amount)
    {
        // derived class code
    }
}

class InterestBearingCheckingAccount : CheckingAccount
{
    public override string GetAccountInfo()
    {
        return "InterestBearingCheckingAccount: Printing account info";
    }
    public new void HideMe()
    {
        Console.WriteLine("InterestBearingCheckingAccount::HideMe");
    }
    public override double GetMinBalance()
    {
        Console.WriteLine("InterestBearingCheckingAccount::GetMinBalance");
        return 1000;
    }
}

sealed class SavingsAccount : Account
{
    double _dblBalance;

    public override string GetAccountInfo()
    {
        return "SavingsAccount: Printing account info";
    }
    public double Withdraw(int accountNumber, double amount)
    {
        _dblBalance = GetBalance(accountNumber);
        if (_dblBalance >= amount)
        {
            _dblBalance -= amount;
            return _dblBalance;
        }
        else
        {
            throw new Exception("Not enough funds.");
        }
    }

    // seal this so it cannot be further overriden
    // override if base class method is abstract
    //public sealed override void Deposit(double amount)
    //{
    //    // derived class code
    //}
    // override if base class method is abstract
    public override void Deposit(double amount)
    {
        // derived class code
    }

}

class Test
{
    public static void Main()
    {
        SavingsAccount oSavingsAccount = new SavingsAccount();
        double balance;
        balance = oSavingsAccount.Withdraw(2, 500);
        Console.WriteLine("balance after withdrawal: " + balance);

        InterestBearingCheckingAccount oIntBrCkAct = new InterestBearingCheckingAccount();
        oIntBrCkAct.Withdraw(500);
        oIntBrCkAct.HideMe();

        CheckingAccount oCheckingAccount = new CheckingAccount();
        oCheckingAccount.Peek();
        oCheckingAccount.Peek(77);

        List<Account> AccountList = new List<Account>();
        AccountList.Add(oSavingsAccount);
        AccountList.Add(oIntBrCkAct);
        AccountList.Add(oCheckingAccount);

        Console.WriteLine("iterate Accounts for info:");
        foreach (var a in AccountList)
        {
            Console.WriteLine("acct info: " + a.GetAccountInfo());
        }

        XCheckingAccount xChkAct = new XCheckingAccount();
        string info = xChkAct.GetAccountInfo();
        Console.WriteLine("X chk acct info: " + info);
        XSavingsAccount xSvgAct = new XSavingsAccount();

        List<IAccount> IAccountList = new List<IAccount>();
        IAccountList.Add(xChkAct);
        IAccountList.Add(xSvgAct);

        Console.WriteLine("iterate IAccounts for info:");
        foreach (var a in IAccountList)
        {
            Console.WriteLine("iacct info: " + a.GetAccountInfo());
        }

    }
}

