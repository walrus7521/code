using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;


namespace proto {
    public class serial {
        public const string COM_PORT = "COM13";
        private int counter = 0;
        private int n_loop = 0;
        private string[] loop = new string[8];
        public static bool _continue;
        private System.ConsoleKey key;
        
        
        public serial() {
            port_name = COM_PORT;
            serialPort = new SerialPort();
            serialPort.BaudRate = 115200;
            serialPort.DataBits = 8;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.DataReceived += port_rx;
            serialPort.PortName = port_name;
        }
        ~serial()
        {
            serialPort.Close();
        }
        public void setport(string com)
        {
            port_name = com;
            serialPort.Close();
            serialPort.PortName = port_name;
            System.Console.WriteLine("setport {0}", port_name);
            connect();
        }
        public void getports()
        {
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            for (int i = 0; i < ports.Length; ++i) {
                System.Console.WriteLine("port {0}", ports[i]);
            }
        }
        public bool connect() {
            System.Console.WriteLine("try to open port {0}", port_name);
            try {
                serialPort.Open();
            } catch (Exception) {
                System.Console.WriteLine("unable to open port {0}", port_name);
                return false;
            }
            System.Console.WriteLine("Yes!!! port {0} is open", port_name);
            return true;
        }
        public void read() {
            string message = serialPort.ReadLine();
            System.Console.WriteLine("read: {0}", message);
       }
        public void write(string s) {
            //byte[] buf = Encoding.ASCII.GetBytes(s);
            //System.Console.WriteLine("sending {0} to serial port", buf);
            //serialPort.Write(buf, 0, s.Length);
            //System.Console.WriteLine("sending {0} to serial port", s);
            serialPort.Write(s);
        }
        private void port_rx(object sender, System.IO.Ports.SerialDataReceivedEventArgs e) {
            counter++;
            //System.Console.WriteLine("{0:X02} got indication", counter % 0xff);
            if (serialPort.IsOpen == true) {
                // Accumulate all data in a string buffer. Always append, so we never lose any data.
                rx_str += serialPort.ReadExisting();
                int idx;
                while ((idx = rx_str.IndexOf('\n')) >= 0) {
                    System.Console.WriteLine("{0:X02}: received: {1}", counter % 0xff, rx_str.Substring(0, idx));
                    rx_str = rx_str.Substring(idx + 1);
                }
            }
        }
        public void bus_pirate_reset()
        {
            write("#");
        }
        public void spi_reset()
        {
            write("0xC0\n");
        }
        public void spi_init()
        {
            write("#\n\n");
            Thread.Sleep(300);
            write("m5\n");
            write("\n\n");
            write("\n\n");
            write("\n\n");
            write("\n\n");
            write("\n\n");
            write("\n\n");
            Thread.Sleep(300);
            write("\n\n");
            write("\n\n");
            write("P\n");
            write("\n\n");
            write("\n\n");
            Thread.Sleep(300);
            write("\n\n");
            write("\n\n");
            write("W\n");
            write("\n\n");
            write("\n\n");
            Thread.Sleep(300);
        }
        public void load(string file = @"spi.pi")
        {
            string[] lines = System.IO.File.ReadAllLines(file);
            n_loop = 0;
            foreach (string line in lines) {
                //loop[n_loop++] = line;
                loop[n_loop++] = line + "\n";
            //    byte[] buf = Encoding.ASCII.GetBytes(line);
            //    loop[n_loop] = Encoding.ASCII.GetString(buf);
            //    //loop[n_loop++] = line.TrimEnd( '\r', '\n' );
            //    System.Console.WriteLine("line = {0}", loop[n_loop]);
            }
            //n_loop = 2;
            //loop[0] = "{0xC0\n";
            //loop[1] = "r]";
            //n_loop = 2;
            //loop[0] = "[3,1]\n";
            //loop[1] = "[r]\n";
            System.Console.WriteLine("n_loop = {0}", n_loop);
            for (int i = 0; i < n_loop; i++) {
                System.Console.WriteLine("loop[{0}] = {1}", i, loop[i]);
            }
            //loop[0] = "[3,1]\n";
            //loop[1] = "{0xC0\n";
            //n_loop = 2;
            //loop[0] = "{0xC0\n";
            //loop[1] = "r]";
        }
        private void check_ui()
        {
            if (Console.KeyAvailable) {
                key = Console.ReadKey(true).Key;
                //System.Console.WriteLine("got key {0}", key);
                if (key == ConsoleKey.Escape) {
                    _continue = false;
                }
            }
        }
        public void run()
        {
            int pc = 0;
            while (_continue) {
                for (pc = 0; pc < n_loop; pc++) {
                    write(loop[pc]);
                    Thread.Sleep(30);
                }
                Thread.Sleep(300);
                check_ui();
            }
        }
        public string port_name;
        private SerialPort serialPort;
        private string rx_str = string.Empty;
    }

    static class Program {


        public static void ui()
        {
            while (proto.serial._continue) {
                try {
                    string cmd = System.Console.ReadLine();
                    if (cmd == "stop") {
                        proto.serial._continue = false;
                    }
                }
                catch (TimeoutException) { }
            }
        }

        //[STAThread]
        [MTAThread]
        static void Main() {
            //Thread uiThread = new Thread(ui);
            //proto.serial._continue = true;
            //uiThread.Start();

            proto.serial port  = new proto.serial();
            if (!port.connect()) {
                return;
            }
            port.bus_pirate_reset();
            port.spi_init();
            port.spi_reset();
            port.load();
            while (true) {
                System.Console.Write("{0}> ", port.port_name);
                string cmd = System.Console.ReadLine();
                if (cmd == "") continue;
                if (cmd == "quit") {
                    //uiThread.Join();
                    return;
                }
                else if (cmd == "init") {
                    port.spi_init();
                }
                else if (cmd == "reset") {
                    port.write("0xC0\n");
                }
                else if (cmd == "load") {
                    System.Console.Write("Enter file to load: ");
                    string file = System.Console.ReadLine();
                    port.load(file);
                }
                else if (cmd == "cs") {
                    port.write("[]\n");
                }
                else if (cmd == "lo") {
                    port.write("[\n");
                }
                else if (cmd == "hi") {
                    port.write("]\n");
                }
                else if (cmd == "run") {
                    proto.serial._continue = true;
                    port.run();
                }
                else if (cmd == "list") {
                    port.getports();
                }
                else if (cmd.Length > 4 && cmd.Substring(0,3) == "put") {
                    string io_cmd = cmd.Substring(4).ToString();
                    io_cmd += "\n";
                    port.write(io_cmd);
                }
                else if (cmd.Length > 4 && cmd.Substring(0,3) == "get") {
                    port.read();
                }
                else {                    
                    //System.Console.Write("Huh??? {0} \n", cmd);
                    string io_cmd = cmd;
                    io_cmd += "\n";
                    System.Console.Write("writing {0} to port\n", io_cmd);
                    port.write(io_cmd);
                }

            }
        }
    }
}
