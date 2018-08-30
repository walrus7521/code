import javax.swing.*;

public class S1P3 {
    public static void main(String[] args) throws Exception {
        int num1 = (int) (Math.round(Math.random()*10));
        int num2 = (int) (Math.round(Math.random()*10));
        int sign = (int) (Math.round(Math.random()*3));
        int answer;

        System.out.println("\n\n*****");

        if (sign == 0) {
            System.out.println(num1 + " * " + num2);
            answer = num1 * num2;
        } else
        if (sign == 1) {
            System.out.println(num1 + " / " + num2);
            answer = num1 / num2;
        } else 
        if (sign == 2) {
            System.out.println(num1 + " + " + num2);
            answer = num1 + num2;
        } else
        if (sign == 3) {
            System.out.println(num1 + " - " + num2);
            answer = num1 - num2;
        } else {
            System.out.println(num1 + " % " + num2);
            answer = num1 % num2;
        }
        System.out.println("*****\n");

        System.out.println("3 ... ");
        Thread.sleep(1000);
        System.out.println("2 ... ");
        Thread.sleep(1000);
        System.out.println("1 ... ");
        Thread.sleep(1000);

        System.out.println("ANSWER: " + answer);

    }
}
