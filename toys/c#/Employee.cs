using System;

namespace Activity6_1
{
    class Employee
    {
        private int _empID;
        private int _ssn;
        private string _loginName;
        private string _password;
        private int _securityLevel;
        private string _name;
        private string _department;

        private int GetNextID()
        {
            // simulates retrieval from database
            return 100;
        }
        public int EmployeeID
        {
            get { return _empID;  }
        }
        public int SSN
        {
            get { return _ssn; }
            set { _ssn = value;  }
        }
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        public string Department
        {
            get { return _department; }
            set { _department = value; }
        }
        public string LoginName
        {
            get { return _loginName; }
            set { _loginName = value;  }
        }
        public string Password
        {
            get { return _password; }
            set { _password = value; }
//                if (value.Length >= 6)
//                {
//                    _password = value;
//                }
//                else
//                {
//                    throw new Exception("Password must be at least 6 characters.");
//                }
//               
//                _password = value; }
        }
        public int SecurityLevel
        {
            get { return _securityLevel;  }
        }

        public void Login(string loginName, string password)
        {
            LoginName = loginName;
            Password = password;
            // Data normally retrieved from database.
            // Hard coded for demo only.
            if (LoginName == "Smith" & password == "js")
            {
                _empID = 1;
                _securityLevel = 2;
            }
            else if (LoginName == "Jones" & password == "mj")
            {
                _empID = 2;
                _securityLevel = 4;
            }
            else
            {
                throw new Exception("Login incorrect.");
            }
        }
        // constructors
        public Employee()
        {
            _empID = GetNextID();
        }
        public Employee(int empID)
        {
            if (empID == 1)
            {
                _empID = 1;
                LoginName = "Smith";
                Password = "js";
                Department = "IT";
                Name = "Jerry Smith";
            }
            else if (empID == 2)
            {
                _empID = 2;
                LoginName = "Jones";
                Password = "mj";
                Department = "HR";
                Name = "Mary Jones";
            }
            else
            {
                throw new Exception("Invalid EmployeeID");
            }
        }
        // overloaded methods
        public int AddEmployee(string loginName, string password, string department, string name)
        {
            _empID = 3;
            LoginName = loginName;
            Password = password;
            Department = department;
            Name = name;
            return EmployeeID;
        }
        public int AddEmployee(string department, string name)
        {
            _empID = 3;
            Department = department;
            Name = name;
            return EmployeeID;
        }
        public string Update(string loginName, string password)
        {
            LoginName = loginName;
            Password = password;
            return "Security info updated.";
        }
        public string Update(int ssNumber, string department)
        {
            SSN = ssNumber;
            Department = department;
            return "HR info updated.";
        }
        
        static void Main()
        {
            Employee oEmployee = new Employee();
            oEmployee.Login("Smith", "js");
            Console.WriteLine("your security level is: " + oEmployee.SecurityLevel);
        }


    }

}
