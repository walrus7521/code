import javax.swing.*;

public class S1P4 {
    public static void main(String[] args) throws Exception {
        int difficulty;
        difficulty = Integer.parseInt(JOptionPane.showInputDialog("How good are you?\n"+
                    "1 = evil genius...\n" + "1= evil, but not a genius"));

        boolean cont = false;
        do {
            // reset cont to false;
            cont = false;

            double num1 = (int) (Math.round(Math.random()*10));
            double num2;
            do {
                num2 = (int) (Math.round(Math.random()*10));
            } while (num2 == 0.0);

            int sign = (int) (Math.round(Math.random()*3));
            double answer;
            System.out.println("\n\n*****");

            if (sign == 0) {
                System.out.println(num1 + " times " + num2);
                answer = num1 * num2;
            } else
            if (sign == 1) {
                System.out.println(num1 + " divided by " + num2);
                answer = num1 / num2;
            } else
            if (sign == 2) {
                System.out.println(num1 + " plus " + num2);
                answer = num1 + num2;
            } else
            if (sign == 3) {
                System.out.println(num1 + " minus " + num2);
                answer = num1 - num2;
            } else {
                System.out.println(num1 + " % " + num2);
                answer = num1 % num2;
            }
            System.out.println("*****\n");

            for (int i = difficulty; i >= 0; --i) {
                System.out.println(i + "...");
                Thread.sleep(500); // 0.5 seconds
            }

            System.out.println("ANSWER: " + answer);

            String again;
            again = JOptionPane.showInputDialog("Play again?");
            if (again.equals("yes")) {
                cont = true;
            }

        } while (cont);

    }
}
