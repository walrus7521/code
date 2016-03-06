import java.util.Vector;
//import java.util.Array;

public class p06_01 {

    static void swap(int[] a, int i, int j)
    {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    static void three_way_partition(int[] a, int pivot)
    {
        int smaller = 0, equal = 0, larger = a.length-1;
        while (equal <= larger) {
            if (a[equal] < pivot) {
                swap(a, smaller++, equal++);
            } else if (a[equal] == pivot) {
                equal++;
            } else {
                swap(a, equal, larger--);
            }
        }
    }

    static void show(int[] a)
    {
        for (int i = 0; i < a.length; ++i) {
            System.out.format("a[%d]= %d\n", i, a[i]);
        }
    }

    public static void main(String[] args) {
        int[] a = {5,4,5,21,6,4,2,5,9};
        System.out.println("pre partition");
        show(a);
        three_way_partition(a, 5);
        System.out.println("post partition");
        show(a);
    }
}
