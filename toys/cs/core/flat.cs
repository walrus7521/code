using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
 
// http://www.softwareandfinance.com/CSharp/Student_DB_Handle.html 
namespace TaskList
{
    class CursorPos
    {
        [StructLayout(LayoutKind.Sequential)]
        struct POSITION
        {
            public short x;
            public short y;
        }
 
        [DllImport("kernel32.dll", EntryPoint = "GetStdHandle", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        private static extern int GetStdHandle(int nStdHandle);
 
        [DllImport("kernel32.dll", EntryPoint = "SetConsoleCursorPosition", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        private static extern int SetConsoleCursorPosition(int hConsoleOutput, POSITION dwCursorPosition);
 
        [DllImport("kernel32.dll", EntryPoint = "FillConsoleOutputCharacter", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        private static extern int FillConsoleOutputCharacter(int hConsoleOutput, byte cCharacter, int nLength, POSITION dwWriteCoord, ref int lpNumberOfCharsWritten);
 
        public static void clrscr()
        {
            int STD_OUTPUT_HANDLE = -11;
            POSITION pos;
            pos.x = pos.y = 0;
            int writtenbytes = 0;
            FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), 32, 80 * 25, pos, ref writtenbytes);
        }
 
        public static void gotoxy(int x, int y)
        {
            int STD_OUTPUT_HANDLE = -11;
            POSITION pos;
            pos.x = (short)x;
            pos.y = (short)y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        }
 
        public static void gotoxy(short x, short y)
        {
            int STD_OUTPUT_HANDLE = -11;
            POSITION pos;
            pos.x = x;
            pos.y = y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        }
    };
 
    class Program
    {
 
        const string prog_name = "Software Project/Task List";

    struct CTask
    {
        public string name;
        public Int32 loe;
        public string dept;
    };
 
    struct CTasks
    {
        string m_fileName;
        public int m_nMaxTasks;
        public CTask [] m_taskList;
 
        public CTasks(string filename)
        {
            m_nMaxTasks = 0;
            m_fileName = filename;
            m_taskList = new CTask[100];
        }
 
        public void AddRecord(string name, Int32 loe, string dept)
        {
            int pos = m_nMaxTasks;
            m_taskList[pos].name = name;
            m_taskList[pos].dept = dept;
            m_taskList[pos].loe = loe;
            m_nMaxTasks++;
            WriteRecords();
        }
 
        public void EditRecord(int pos, string name, Int32 loe, string dept)
        {
            m_taskList[pos].name = name;
            m_taskList[pos].dept = dept;
            m_taskList[pos].loe = loe;
            WriteRecords();
        }
 
        public void DeleteRecord(int pos)
        {
            m_nMaxTasks--;
 
            for(int i = pos; i < m_nMaxTasks; i++)
            {
                m_taskList[i] = m_taskList[i + 1];
            }
            WriteRecords();
        }
 
        public int ReadRecords()
        {
            try
            {
                System.IO.BinaryReader istream = new System.IO.BinaryReader(System.IO.File.Open(m_fileName, System.IO.FileMode.Open));
 
                if (istream == null)
                    return -1;
 
                Byte[] buf = new Byte[4096];
                int nTotalRecordsRead = 0;
 
                for (int i = 0; i < 100; i++)
                {
                    int t = istream.PeekChar();
                    if (t == -1)
                        break;
                        
                    m_taskList[i].name = istream.ReadString();
                    m_taskList[i].loe = istream.ReadInt32();
                    m_taskList[i].dept = istream.ReadString();
                    nTotalRecordsRead++;
                }
 
                istream.Close();
                m_nMaxTasks = nTotalRecordsRead;
 
                return nTotalRecordsRead;
            }
            catch(Exception e)
            {
                //Console.WriteLine("Exception information: {0}", e);          
                return -1;
            }
        }
 
        public int WriteRecords()
        {
            System.IO.BinaryWriter ostream = new System.IO.BinaryWriter(System.IO.File.Open(m_fileName, System.IO.FileMode.OpenOrCreate));
 
            if (ostream == null)
                return -1;
 
            int nTotalRecordsWritten = 0;
            char [] buf = new char[4096];
 
            for(int i = 0; i < m_nMaxTasks; i++)
            {
                ostream.Write(m_taskList[i].name);
                ostream.Write(m_taskList[i].loe);
                ostream.Write(m_taskList[i].dept);
                nTotalRecordsWritten++;
            }
 
            ostream.Close();
 
            return nTotalRecordsWritten;
        }
    };
 
 
    public static void ViewRecords()
    {
        theTasks.ReadRecords();
       
        CursorPos.clrscr();
           
        CursorPos.gotoxy(10,4);
        Console.Write(prog_name);
 
        CursorPos.gotoxy(10,5);
        Console.Write("___________________________________________");
 
        CursorPos.gotoxy(10,6);
        Console.Write("SNo Task Name       Level of Effort    Department   ");
 
        CursorPos.gotoxy(10,7);
        Console.Write("___________________________________________");
 
        int pos = 8;
        // Enable Paging
        for(int i = 0; i < theTasks.m_nMaxTasks; i++)
        {
            CursorPos.gotoxy(10,pos);
            Console.Write(i + 1);
            CursorPos.gotoxy(14,pos);
            Console.Write(theTasks.m_taskList[i].name);
            CursorPos.gotoxy(33,pos);
            Console.Write(theTasks.m_taskList[i].loe);
            CursorPos.gotoxy(42,pos);
            Console.Write(theTasks.m_taskList[i].dept);
            pos++;
        }
        CursorPos.gotoxy(10,pos++);
        Console.Write("___________________________________________");
        pos++;
        CursorPos.gotoxy(10,pos++);
    }
 
 
    public static void InputRecords()
    {
        while(true)
        {
            CursorPos.clrscr();
           
            CursorPos.gotoxy(10,4);
            Console.Write(prog_name);
 
            CursorPos.gotoxy(10,5);
            Console.Write("___________________________________________");
 
            CursorPos.gotoxy(10,6);
            Console.Write("Task Name: ");
 
            CursorPos.gotoxy(10,7);
            Console.Write("LoE: ");
 
            CursorPos.gotoxy(10,8);
            Console.Write("Dept: ");
 
            CursorPos.gotoxy(10,9);
            Console.Write("___________________________________________");
 
            CursorPos.gotoxy(23,6);
            string name;
            name = Console.ReadLine();
 
            CursorPos.gotoxy(17,7);
            int loe;
            loe = Convert.ToInt32(Console.ReadLine());
 
            CursorPos.gotoxy(23,8);
            string dept;
            dept = Console.ReadLine();
 
            theTasks.AddRecord(name, loe, dept);
 
            CursorPos.gotoxy(10,11);
            Console.Write("Do you want to add another record (Y/N)? ");
            char ch = Convert.ToChar(Console.ReadLine());
 
            if(ch == 'Y' || ch == 'y')
                continue;
            else
                break;
        }
    }
 
 
    public static void EditRecords()
    {
        ViewRecords();
        Console.Write("Enter the serial number you want to edit: ");
        int m;
        m = Convert.ToInt32(Console.ReadLine());
 
        if(m >= 1 && m <= theTasks.m_nMaxTasks)
        {
            CursorPos.clrscr();
            CursorPos.gotoxy(10,4);
            Console.Write(prog_name);
 
            CursorPos.gotoxy(10,5);
            Console.Write("___________________________________________");
 
            CursorPos.gotoxy(10,6);
            Console.Write("Task Name: ");
 
            CursorPos.gotoxy(10,7);
            Console.Write("LoE: ");
 
            CursorPos.gotoxy(10,8);
            Console.Write("Dept: ");
 
            CursorPos.gotoxy(10,9);
            Console.Write("___________________________________________");
 
            CursorPos.gotoxy(23,6);
            string name;
            name = Console.ReadLine();
 
 
            CursorPos.gotoxy(17,7);
            int loe;
            loe = Convert.ToInt32(Console.ReadLine());
 
            CursorPos.gotoxy(23,8);
            string dept;
            dept = Console.ReadLine();
 
            theTasks.EditRecord(m - 1, name, loe, dept);       
            CursorPos.gotoxy(10,12);
            Console.Write("Record updated. Press any key to return to Main Menu");
            Console.ReadLine();
        }
        else
        {
            CursorPos.gotoxy(10,12);
            Console.ReadLine();
            Console.Write("Invalid Entry. Press any key to return to Main Menu");
            Console.ReadLine();
        }
 
    }
 
    public static void DeleteRecords()
    {
        ViewRecords();
        Console.Write("Enter the serial number you want to delete: ");
        int m;
        m = Convert.ToInt32(Console.ReadLine());
        if(m >= 1 && m <= theTasks.m_nMaxTasks)
        {
            theTasks.DeleteRecord(m - 1);
            Console.Write("          Record deleted. Press any key to return to Main Menu");
            Console.ReadLine();
        }
        else
        {
            Console.Write("          Invalid Entry. Press any key to return to Main Menu");
            Console.ReadLine();
        }
    }
 
    static public string DisplayMainMenu()
    {
       
        CursorPos.clrscr();
        CursorPos.gotoxy(10, 4);
        Console.Write(prog_name);
 
        CursorPos.gotoxy(10, 5);
        Console.Write("___________________________________________");
 
        CursorPos.gotoxy(10,6);
        Console.Write("1. Add Task Record");
 
        CursorPos.gotoxy(10, 7);
        Console.Write("2. Edit Task Record");
 
        CursorPos.gotoxy(10, 8);
        Console.Write("3. View Task Record");
 
        CursorPos.gotoxy(10, 9);
        Console.Write("4. Delete Task Record");
 
        CursorPos.gotoxy(10, 10);
        Console.Write("5. Exit");
 
        CursorPos.gotoxy(10, 11);
        Console.Write("___________________________________________");
 
        CursorPos.gotoxy(10, 13);
        Console.Write("Enter your Selection: ");
        string s = Console.ReadLine();
        return s;
    }
 
 
    static CTasks theTasks;
        static void Main(string[] args)
        {
            theTasks = new CTasks("m:\\code\\swproj.bin");
            theTasks.ReadRecords();
 
 
            while (true)
            {
                string sel = DisplayMainMenu();
                int iselection;
                bool isNumeric = int.TryParse(sel, out iselection);
                if (isNumeric) {
                    switch (iselection)
                    {
                        case 1:
                            InputRecords();
                            break;
                        case 2:
                            EditRecords();
                            break;
                        case 3:
                            {
                                ViewRecords();
                                Console.Write("Press any key to return to Main Manu: ");
                                Console.ReadLine();
                            }
                            break;
                        case 4:
                            DeleteRecords();
                            break;
                        case 5:
                        default:
                            return;
                    };
                }
            }
        }
    }
}
