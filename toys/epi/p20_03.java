
class OddEvenMonitor {
    public static final boolean ODD_TURN = true;
    public static final boolean EVEN_TURN = false;
    private boolean turn = ODD_TURN;

    public synchronized void waitTurn(boolean oldTurn) {
        while (turn != oldTurn) {
            try {
                wait();
            } catch (Exception e) {
            }
        }
    }

    public synchronized void toggleTurn() {
        turn ^= true;
        notify();
    }
}

class OddThread extends Thread {
    private final OddEvenMonitor monitor;

    public OddThread(OddEvenMonitor monitor) {
        this.monitor = monitor;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 100; i+=2) {
            monitor.waitTurn(OddEvenMonitor.ODD_TURN);
            System.out.println(i);
            monitor.toggleTurn();
        }
    }
}

class EvenThread extends Thread {
    private final OddEvenMonitor monitor;

    public EvenThread(OddEvenMonitor monitor) {
        this.monitor = monitor;
    }

    @Override
    public void run() {
        for (int i = 2; i <= 100; i+=2) {
            monitor.waitTurn(OddEvenMonitor.EVEN_TURN);
            System.out.println(i);
            monitor.toggleTurn();
        }
    }
}

public class p20_03 {
    public static int counter;
    public static int N;

    public static void main(String[] args) throws Exception {
        N = (args.length > 0) ? new Integer(args[0]) : 100;
        counter = 0;

        OddEvenMonitor mon = new OddEvenMonitor();
        Thread T1 = new Thread( new OddThread(mon) ); // prints odd
        Thread T2 = new Thread( new EvenThread(mon) ); // prints even

        T1.start(); T2.start();
        T1.join();  T2.join();

    }
}
