import javax.swing.*;

public class S1P2 {
    public static void main(String[] args) {
        String input;
        input = JOptionPane.showInputDialog("Enter the secret message.");
        if (input.equals("Angel Genius")) {
            System.out.println("YOU GOT THE MESSAGE!!");
        } else {
            System.out.println("WOOPS, MESSAGE INCORRECT!!");
        }
    }
}
