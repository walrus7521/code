import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class HelloJava {
    public static void main(String[] args)
    {
        JFrame frame = new JFrame("HelloJava4");
        frame.add(new HelloComponent4("Hello, Java!"));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 300);
        frame.setVisible(true);
    }

}

class HelloComponent2 extends JComponent 
    implements MouseMotionListener
{
    String theMessage;
    int messageX = 125, messageY = 95;

    public HelloComponent2(String message) {
        theMessage = message;
        addMouseMotionListener(this);
    }

    public void paintComponent(Graphics g) {
        g.drawString(theMessage, messageX, messageY);
    }

    public void mouseDragged(MouseEvent e) {
        messageX = e.getX();
        messageY = e.getY();
        repaint();
    }

    public void mouseMoved(MouseEvent e) {}

}

class HelloComponent4 extends JComponent
    implements MouseMotionListener, ActionListener, Runnable
{
    String theMessage;
    int messageX = 125, messageY = 95;

    JButton theButton;

    int colorIndex;
    static Color[] someColors = {
        Color.black, Color.red, Color.green, Color.blue, Color.magenta};

    boolean blinkState;

    public HelloComponent4(String message) {
        theMessage = message;
        theButton = new JButton("Change Color");
        setLayout(new FlowLayout());
        add( theButton ); // method inherited from Container class
        theButton.addActionListener(this);
        addMouseMotionListener(this);
        Thread t = new Thread(this);
        t.start();
    }

    public void paintComponent( Graphics g ) {
        g.setColor(blinkState ? getBackground() : currentColor());
        g.drawString( theMessage, messageX, messageY );
    }

    public void mouseDragged( MouseEvent e ) {
        messageX = e.getX();
        messageY = e.getY();
        repaint();
    }

    public void mouseMoved( MouseEvent e ) {}

    public void actionPerformed( ActionEvent e ) {
        // did somebody push our button?
        if (e.getSource() == theButton) {
            changeColor();
        }
    }

    synchronized private void changeColor() {
        if (++colorIndex == someColors.length)
            colorIndex = 0;
        setForeground( currentColor() );
        repaint();
    }

    synchronized private Color currentColor() {
        return someColors[colorIndex];
    }

    public void run() {
        try {
            while (true) {
                blinkState = !blinkState;
                repaint();
                Thread.sleep(300);
                    
            }
        } catch (InterruptedException e) {}
    }
}

