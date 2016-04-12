using System;

public abstract class Account
{
    int _accountNumber;

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

sealed class CheckingAccount : Account
{
    // override if base class method is abstract
    public override void Deposit(double amount)
    {
        // derived class code
    }
}

sealed class SavingsAccount : Account
{
    double _dblBalance;

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

    }
}

