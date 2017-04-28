
public class HeapTest {
    public static void main(String[] args) {
        Heap h = new Heap(16);
        int i = 0;
        for (i = 0; i < 12; ++i) h.insert(i);
        h.show();
        while (h.nelems > 0) {
            i = h.delete_max();
            System.out.println("max = " + i);
        }
    }
}
