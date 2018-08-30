
public class RingQueue extends Ring {

    RingQueue(int ring_size) {
        super(ring_size);
    }

    void enqueue(int item) {
        put_front(item);
    }

    int dequeue() {
        return get_back();
    }

    public int type() {
        return (int) 'Q';
    }
    
}
