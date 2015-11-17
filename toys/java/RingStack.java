
public class RingStack extends Ring {

    RingStack(int ring_size) {
        super(ring_size);
    }

    void push(int item) {
        put_front(item);
    }

    int pop() {
        return get_front();
    }
    
    public int type() {
        return (int) 'S';
    }
    
}
