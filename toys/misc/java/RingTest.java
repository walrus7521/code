
public class RingTest {

    //private static void RawRingTest() {
    //    Ring r = new Ring(12);
    //    int j = 0;
    //    while (!r.full()) {
    //        r.put_front(j);
    //        j++;
    //    }
    //    while (!r.empty()) {
    //        j = r.get_back();
    //        System.out.println("got " + j + "\n");
    //    }
    //}

    private static void QueueTest() {
        RingQueue q = new RingQueue(12);
        int j = 0;
        while (!q.full()) {
            q.enqueue(j);
            j++;
        }
        while (!q.empty()) {
            j = q.dequeue();
            System.out.println("dequeue " + j + "\n");
        }
    }

    private static void StackTest() {
        RingStack s = new RingStack(12);
        int j = 0;
        while (!s.full()) {
            s.push(j);
            j++;
        }
        while (!s.empty()) {
            j = s.pop();
            System.out.println("pop " + j + "\n");
        }
    }

    private static void GenerateException() {
        RingStack s = new RingStack(12);
        int j = 0;
        while (!s.full()) {
            s.push(j);
            j++;
        }
        s.push(99);
        while (!s.empty()) {
            j = s.pop();
            System.out.println("pop " + j + "\n");
        }
    }

    private static void EqualityTest() {
        RingQueue r = new RingQueue(12);
        RingStack s = new RingStack(21);
        RingQueue t = r;
        if (r == t) {
            System.out.println("r == t");
        } else {
            System.out.println("r != t");
        }
        if (r.equals(t)) {
            System.out.println("r == t");
        } else {
            System.out.println("r != t");
        }
        if (s.equals(t)) {
            System.out.println("s == t");
        } else {
            System.out.println("s != t");
        }
        System.out.println("r is " + r);
        System.out.println("s is " + s);
        System.out.println("t is " + t);
        System.out.println("r is type " + r.type());
        System.out.println("s is type " + s.type());
    }

    public static void main(String[] args) {
        //RawRingTest();
        //QueueTest();
        //StackTest();
        //EqualityTest();
        try {
            GenerateException();
        } catch (IndexOutOfBoundsException e) {
            System.out.println("yo dude you screwed up");
            System.out.println(e.toString());
        }
    }
}
