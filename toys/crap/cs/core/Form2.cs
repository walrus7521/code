using System;
using System.Windows.Forms;

// mcs form2.cs -pkg:dotnet

namespace HelloForms
{
    public class MainForm: Form
    {
        Label label1 = new Label();
        Label label2 = new Label();

        public MainForm ()
        {
            this.SuspendLayout();

            // Initialize your components here
            this.label1.Text = "Hello, World!";
            this.label2.Text = "Hello, Father!";

            this.Controls.Add(label1);
            this.Controls.Add(label2);
            this.ResumeLayout();
            this.Name = "MainForm Name.";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MainForm Title!";

        }
    }

    public class Program
    {
        public static void Main(string[] args) {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm ());
        }
    }
}
