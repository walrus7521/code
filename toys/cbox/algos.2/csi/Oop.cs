using System;


// base classes, derived classes, access modifiers
// override base class methods, implement interfaces,
// implement polym via inheritance & via interfaces

// interfaces are like abstract base classes
public interface IAccount
{
    string GetAccountInfo(int accountNumber);
}

public interface IBranch
{
    string GetBranchInfo(int branchNumber);
}

public class BranchAccount : IAccount, IBranch
{
    public string GetAccountInfo(int accountNumber) {
        return "millionaires account";
    }
    public string GetBranchInfo(int branchNumber) {
        return "kayman branch";
    }
}

// base class
class Account
{
    long _accountNumber;
    public long AccountNumber {
        get { return _accountNumber; }
        set { _accountNumber = value; }
    }
    public double GetBalance() {
        return (double) 10000;
    }
}

// abstract class - can't be directly instantiated, only derived from
abstract class Account1
{
    long _accountNumber;
    public long AccountNumber {
        get { return _accountNumber; }
        set { _accountNumber = value; }
    }
    protected double _balance;
    protected double _GetBalance() {
        return (double) _balance;
    }
    // to allow a derived class to override a method
    // define the method as virtual
    public virtual void Deposit(double amount) {
        _balance += amount;
    }
}

// pure abstract base classes only have signatures
public abstract class Account2
{
    public abstract void Deposit(double amount);
}

// access modifiers in base classes
// public - accessible by derived class and client
// private - not accessible by derived class or client
// protected - accessible by derived class but not client
// sealed - prevents further inheritance or overrides

sealed class CheckingAccount : Account1
{
    double _minBalance;
    public double MinBalance {
        get { return _minBalance; }
        set { _minBalance = value; }
    }
    public void Withdraw(double amount) {
        _balance -= amount;
    }
    public double GetBalance() {
        return base._GetBalance();
    }
    // we can now override Deposit method
    public sealed override void Deposit(double amount) {
        _balance += amount * 1.1;
    }
}

class Employee
{
    private string _name;
    private string _password;
    private int _id;
    // getter and setters in classes
    public string Name {
        get { return _name; }
        set { _name = value; }
    }
    //readonly
    public string Name2 {
        get { return _name; }
    }
    // writeonly
    public string Password {
        set { 
            if (value.Length > 7) {
                _password = value; 
                Console.WriteLine("passwd: {0}", _password);
            } else {
                throw new Exception("passwd must be at least 7 chars");
            }
        }
    }
    // methods
    public void Login(string loginName, string password)
    {
    }
    // ctors
    public Employee(string name)
    {
        Console.WriteLine("ctor - default {0}", name);
        _name = name;
    }
    public Employee(int id)
        : this("dude")
    {
        _id = id;
        Console.WriteLine("ctor id: {0}", id);
    }
    // dtor
    ~Employee()
    {
        Console.WriteLine("dtor");
    }
}

public class Tester
{
    public static void Main()
    {
        Employee e = new Employee(7);
        Console.WriteLine("hello");
        e.Name = "The dude";
        e.Password = "noooddddles";
        Console.WriteLine("my name is: {0}", e.Name);

        CheckingAccount chk = new CheckingAccount();
        chk.AccountNumber = 0xbeef;
        Console.WriteLine("acct: {0:x}", chk.AccountNumber);
        chk.Deposit(500);
        Console.WriteLine("balance: {0}", chk.GetBalance());
        chk.Withdraw(500);
        Console.WriteLine("balance: {0}", chk.GetBalance());

        BranchAccount bact = new BranchAccount();
        Console.WriteLine("branch account info: {0}, branch info: {1}",
                bact.GetAccountInfo(42), bact.GetBranchInfo(17));
    }
}
