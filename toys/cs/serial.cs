using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;

namespace proto {
    public class serial {
        //public const string COM_PORT = "COM31"; // ADP
        //public const string COM_PORT = "COM32"; // MCPA
        //public const string COM_PORT = "COM33"; // MCPB
        public const string COM_PORT = "COM34"; // MCPC
        public serial() {
            serialPort = new SerialPort();
            serialPort.BaudRate = 115200;
            serialPort.DataBits = 8;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.DataReceived += port_rx;
            serialPort.PortName = COM_PORT;
        }
        ~serial()
        {
            serialPort.Close();
        }
        public bool connect() {
            try {
                serialPort.Open();
            } catch (Exception) {
                System.Console.WriteLine("unable to open port {0}", COM_PORT);                
                return false;
            }
            return true;
        }
        public void write(string s) {
            //byte[] buf = Encoding.ASCII.GetBytes(s);
            //System.Console.WriteLine("sending {0} to serial port", buf);
            //serialPort.Write(buf, 0, s.Length);
            System.Console.WriteLine("sending {0} to serial port", s);
            serialPort.Write(s);
        }
        private void port_rx(object sender, System.IO.Ports.SerialDataReceivedEventArgs e) {
            
            System.Console.WriteLine("got indication");
            if (serialPort.IsOpen == true) {
                // Accumulate all data in a string buffer. Always append, so we never lose any data.
                rx_str += serialPort.ReadExisting();
                int idx;
                while ((idx = rx_str.IndexOf('\n')) >= 0) {
                    System.Console.WriteLine("received: {0}", rx_str.Substring(0, idx));
                    rx_str = rx_str.Substring(idx + 1);
                }
            }
        }
        private SerialPort serialPort;
        private string rx_str = string.Empty;
    }

    static class Program {
        [STAThread]
        static void Main() {
            proto.serial port  = new proto.serial();
            if (!port.connect()) {
                return;
            }
            while (true) {
                System.Console.Write("$ ");
                string cmd = System.Console.ReadLine();
                if (cmd == "quit") {
                    return;
                }
                port.write(cmd);

            }
        }
    }
}
