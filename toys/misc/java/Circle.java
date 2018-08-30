

public class Circle {
    static final double PI = 3.14159;

    public static void main(String[] args) {
        int radius;
        double area;

        radius = Integer.parseInt(args[0]);
        area = PI * (radius * radius);
        System.out.println("A circle of radius " + args[0] 
                + " has are of " + area);

    }
}
