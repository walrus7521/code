using System;

// need to update the view based on user input
//  ie, the Label and SpeedControl

// https://msdn.microsoft.com/en-us/library/ms229597(v=vs.100).aspx

public class SatNavModel
{
    // The directions we can travel
    public enum TravelDirection
    {
        Still, North, South, East, West
    }

    // Change handler
    public event EventHandler ModelChanged;

    // The current direction and speed
    private TravelDirection CurrentDirection;
    private int CurrentSpeed;

    public SatNavModel()
    {
        CurrentDirection = TravelDirection.North;
        CurrentSpeed = 0;
    }

    public virtual TravelDirection Direction
    {
        set
        {
            if (value != CurrentDirection)
            {
                CurrentDirection = value;
                if (ModelChanged != null)
                {
                    Console.WriteLine("model change: direction = " + value.ToString());
                    ModelChanged(this, EventArgs.Empty);
                }
            }
        }
        get
        {
            return CurrentDirection;
        }
    }

    public virtual int Speed
    {
        set
        {
            if (value != CurrentSpeed)
            {
                CurrentSpeed = value;
                if (ModelChanged != null)
                {
                    Console.WriteLine("model change: speed = " + value.ToString());
                    ModelChanged(this, EventArgs.Empty);
                }
            }
        }
        get
        {
            return CurrentSpeed;
        }
    }
}

class Button
{
    public bool Enabled;
}

class Label
{
    public string Text;
}

public class SpeedControl
{
    public int Value;
}

public partial class SatNavView
{
    private SatNavModel model;
    public event EventHandler ViewControlActivated;
    private Button northButton;
    private Button southButton;
    private Button eastButton;
    private Button westButton;
    private Label feedbackLabel;
    public SpeedControl speedControl;

    public SatNavView(SatNavModel model)
    {
        //InitializeComponent();
        this.model = model;
        this.model.ModelChanged += HandleModelChanged;

        northButton     = new Button();
        southButton     = new Button();
        eastButton      = new Button();
        westButton      = new Button();
        feedbackLabel   = new Label();
        speedControl    = new SpeedControl();

        this.SatNavView_Load(null, EventArgs.Empty);

    }

    private void SatNavView_Load(Object sender, EventArgs e)
    {
        northButton.Enabled = false;
        feedbackLabel.Text = "You are pointing " + model.Direction +
            " but not yet moving.  Use buttons and speed control";
    }

    public void HandleModelChanged(Object sender, EventArgs e)
    {
        feedbackLabel.Text = "view update: Direction: " + model.Direction +
            ", speed: " + model.Speed;
        Console.WriteLine(feedbackLabel.Text);
    }

    public void eastButton_Click(object sender, EventArgs e)
    {
        Console.WriteLine("button press: East");
        if (ViewControlActivated != null)
        {
            ControlEventArgs args = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.East;
            ViewControlActivated(this, args);
        }
    }
    public void northButton_Click(object sender, EventArgs e)
    {
        Console.WriteLine("button press: North");
        if (ViewControlActivated != null)
        {
            ControlEventArgs args = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.North;
            ViewControlActivated(this, args);
        }
    }
    public void southButton_Click(object sender, EventArgs e)
    {
        Console.WriteLine("button press: South");
        if (ViewControlActivated != null)
        {
            ControlEventArgs args = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.South;
            ViewControlActivated(this, args);
        }
    }
    public void westButton_Click(object sender, EventArgs e)
    {
        Console.WriteLine("button press: West");
        if (ViewControlActivated != null)
        {
            ControlEventArgs args = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.West;
            ViewControlActivated(this, args);
        }
    }
    public void speedControl_ValueChanged(object sender, EventArgs e)
    {
        Console.WriteLine("button press: Speed");
        if (ViewControlActivated != null)
        {
            ControlEventArgs args = new ControlEventArgs();
            args.speed = (int) speedControl.Value;
            ViewControlActivated(this, args);
        }
    }

    internal void enableAllowedButtons()
    {
        // Enable all direction buttons
        eastButton.Enabled = true;
        northButton.Enabled = true;
        southButton.Enabled = true;
        westButton.Enabled = true;

        // Disable current direction button
        if (model.Direction == SatNavModel.TravelDirection.East)
        {
            eastButton.Enabled = false;
        }
        else if (model.Direction == SatNavModel.TravelDirection.North)
        {
            northButton.Enabled = false;
        }
        else if (model.Direction == SatNavModel.TravelDirection.South)
        {
            southButton.Enabled = false;
        }
        else if (model.Direction == SatNavModel.TravelDirection.West)
        {
            westButton.Enabled = false;
        }

    }

    public class ControlEventArgs : EventArgs
    {
        public SatNavModel.TravelDirection direction;
        public int speed;
    }

}

public class SatNavController
{
    // Need a reference to both the model and the view
    private SatNavModel model;
    private SatNavView view;

    public SatNavController(SatNavModel model, SatNavView view)
    {
        this.model = model;
        this.view = view;
        this.view.ViewControlActivated += HandleViewControlActivated;
    }

    public void HandleViewControlActivated(Object sender, EventArgs args)
    {
        SatNavView.ControlEventArgs satnavArgs
            = (SatNavView.ControlEventArgs) args;
        if (satnavArgs.direction
                != SatNavModel.TravelDirection.Still)
        {
            Console.WriteLine("control notification - direction: " + satnavArgs.direction.ToString());
            model.Direction = satnavArgs.direction;
            view.enableAllowedButtons();
        }
        else
        {
            Console.WriteLine("control notification - speed: " + satnavArgs.speed.ToString());
            model.Speed = satnavArgs.speed;
        }
    }

}

class Client
{
    public static void Parse(string line)
    {
    }

    public static void Main()
    {

        SatNavModel model = new SatNavModel();
        SatNavView view = new SatNavView(model);
        SatNavController controller = new SatNavController(model, view);

        string line;
        EventArgs e = new EventArgs();
        while (true)
        {
            Console.Write("$ ");
            line = Console.ReadLine();
            if (line == "north") {
                view.northButton_Click(null, e);
            } else if (line == "south") {
                view.southButton_Click(null, e);
            } else if (line == "east") {
                view.eastButton_Click(null, e);
            } else if (line == "west") {
                view.westButton_Click(null, e);
            } else if (line == "speed") {
                view.speedControl.Value = 70;
                view.speedControl_ValueChanged(null, e);
            } else if (line == "clear") {
                Console.Clear();
            } else if (line == "quit") {
                return;
            }
        }
    }
}

