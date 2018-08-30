

public class Multiply {
    public static void main(String[] args) {
        String resultString;
        int arg1, arg2, result;

        arg1 = Integer.parseInt(args[0]);
        arg2 = Integer.parseInt(args[1]);
        result = arg1 + arg2;

        resultString = Integer.toString(result);
        System.out.println("The product of " + args[0] +
                " and " + args[1] + " is " + resultString);

    }
}
