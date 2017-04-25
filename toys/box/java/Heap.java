
public class Heap {

    private int AA[];
    private int max = 0;
    public int nelems = 0;

    public Heap(int size) {
        AA = new int [size];
        max = nelems = 0;
    }

    private void swap(int x, int y) {
        int tmp;
        tmp = AA[x]; AA[x] = AA[y]; AA[y] = tmp;
    }

    private void perc_up(int k, int x) {
        while (k > 1 && x > AA[k/2]) {
            AA[k] = AA[k/2]; k /= 2;
        }
        AA[k] = x;
    }

    private void perc_down(int k) {
        int c;
        c = 2 * k;
        while (c < nelems) {
            if (c < nelems-1 && AA[c] < AA[c+1]) ++c;
            if (AA[k] < AA[c]) {
                swap(k, c);
                k = c;
                c = 2 * c;
            } else break;
            ++c;
        }
    }

    public void insert(int x) {
        System.out.println("insert: " + x);
        perc_up(++nelems, x);
    }

    public int delete_max() {
        int x = AA[1];
        --nelems;
        swap(1, nelems);
        perc_down(1);
        return x;
    }

    public void show() {
        int i;
        for (i = 1; i <= nelems; ++i)
            System.out.printf("[%d]  ", AA[i]);
        System.out.println();
    }

}
