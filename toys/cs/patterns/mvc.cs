using System;

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

public partial class SatNavView : Form
{
    private SatNavModel model;
    public event EventHandler ViewControlActivated;

    public SatNavView(SatNavModel model)
    {
        InitializeComponent();
        this.model = model;
        this.model.ModelChanged += HandleModelChanged;
    }

    private void SatNavView_Load(Object sender, EventArgs e)
    {
        northButton.Enabled = false;
        feedbackLabel.Text = "You are pointing " + model.Direction +
            " but not yet moving.  Use buttons and speed control";
    }

    public void HandleModelChanged(Object sender, EventArgs e)
    {
        feedbackLabel.Text = "Direction: " + model.Direction +
            ", speed: " + model.Speed;
    }

    public void eastButton_Click(object sender, EventArgs e)
    {
        if (ViewControlActivated != null)
        {
            ControlEventArgs afgs = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.East;
            ViewControlActivated(this, args);
        }
    }
    public void northButton_Click(object sender, EventArgs e)
    {
        if (ViewControlActivated != null)
        {
            ControlEventArgs afgs = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.North;
            ViewControlActivated(this, args);
        }
    }
    public void southButton_Click(object sender, EventArgs e)
    {
        if (ViewControlActivated != null)
        {
            ControlEventArgs afgs = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.South;
            ViewControlActivated(this, args);
        }
    }
    public void westButton_Click(object sender, EventArgs e)
    {
        if (ViewControlActivated != null)
        {
            ControlEventArgs afgs = new ControlEventArgs();
            args.direction = SatNavModel.TravelDirection.West;
            ViewControlActivated(this, args);
        }
    }
    public void speedControl_ValueChanged(object sender, EventArgs e)
    {
        if (ViewControlActivated != null)
        {
            ControlEventArgs afgs = new ControlEventArgs();
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
        else if (model.Direction == SavNavModel.TravelDirection.North)
        {
            northButton.Enabled = false;
        }
        else if (model.Direction == SavNavModel.TravelDirection.South)
        {
            southButton.Enabled = false;
        }
        else if (model.Direction == SavNavModel.TravelDirection.West)
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
            model.Direction = satnavArgs.direction;
            view.enableAllowedButtons();
        }
        else
        {
            model.Speed = satnavArgs.Speed;
        }
    }

}

class Client
{
    public static void Main()
    {
    }
}

