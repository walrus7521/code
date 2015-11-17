/*
 * QueueDemo
 * Implementation of a FIFO queue ADT in Java
 * Chapter 2, Section 2.1.2
 * By Derek Hao Hu (derekhh@cse.ust.hk)
 */

public class QueueDemo {
    public static void main(String[] args) {
        queue q = new queue();
        for(int i=0;i<10;i++)
            q.enqueue(i);
        for(int i=0;i<10;i++)
            System.out.printf("%d\n",q.dequeue());
    }
}
