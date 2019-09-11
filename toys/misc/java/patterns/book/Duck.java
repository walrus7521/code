
public interface QuackBehavior {
    public void quack();
}
public interface FlyBehavior {
    public void fly();
}

public abstract class Duck {

    FlyBehavior   flyBehavior;
    QuackBehavior quackBehavior;

    public Duck() {
    }
    public abstract void display();

    public void performQuack() {
        quackBehavior.quack();
    }
    public void performFly() {
        flyBehavior.fly();
    }
    public void swim() {
        System.out.println("All ducks float, even decoys");
    }
    public void display() {
    }
}

public class MallardDuck extends Duck {
    public MallardDuck() {
        quackBehavior = new Quack();
        flyBehavior = new FlyWithWings();
    }
    public void display() {
        System.out.println("I'm a real Mallard duck");
    }
}

class Main {
    public static void main(String args[]) {
    }

}

