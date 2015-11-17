public class queue {
    public final int QUEUESIZE = 1000;
    int q[];
    int first;
    int last;
    int count;
    queue() {
        q = new int [QUEUESIZE + 1];
        first = 0;
        last = QUEUESIZE - 1;
        count = 0;
    }
    void enqueue(int x) {
        if(count >= QUEUESIZE)
            System.out.printf("Warning: queue overflow enqueue x = %d\n", x);
        else {
            last = (last + 1) % QUEUESIZE;
            q[last] = x;
            count++;
        }
    }
    int dequeue() {
        int x;
        if(count <= 0) {
            System.out.printf("Warning: empty queue dequeue.\n");
            return -1;
        } else {
            x = q[first];
            first = (first + 1) % QUEUESIZE;
            count--;
            return x;
        }
    }
    boolean empty() {
        if(count <= 0)
            return true;
        else
            return false;
    }
    void show_queue() {
        for(int i=first,cnt=0;cnt<=count;i=(i+1)%QUEUESIZE,cnt++)
            System.out.printf("%d ",q[i]);
        System.out.printf("\n");
    }
}
