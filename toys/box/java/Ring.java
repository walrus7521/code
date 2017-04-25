abstract class Ring implements BaseRing {

    private int buffer[];
    private int read, write, size;

    public Ring(int ring_size) {
        buffer = new int [ring_size];
        read = write = 0;
        size = ring_size;
    }

    public boolean full() {
        if (read == (write+2)%size) {
            return true;
        }
        return false;
    }

    public boolean empty() {
        if (read == write) {
            System.out.println("is empty[rd=" + read + ", wr=" + write + "]");
            return true;
        }
        System.out.println("is not empty");
        return false;
    }

    public void put_front(int item) throws IndexOutOfBoundsException {
        if (full()) {
            throw new IndexOutOfBoundsException();
        }
        buffer[write] = item;
        System.out.println("put[" + write + "] = " + item);
        ++write;
        write %= size;
    }

    public int get_back() throws IndexOutOfBoundsException {
        int item;
        if (empty()) {
            throw new IndexOutOfBoundsException();
        }
        item = buffer[read];
        System.out.println("get[" + read +  "] = " + item);
        ++read;
        read %= size;
        return item;
    }

    public int get_front() throws IndexOutOfBoundsException {
        int item;
        if (empty()) {
            throw new IndexOutOfBoundsException();
        }
        --write;
        write %= size;
        item = buffer[write];
        System.out.println("pop[" + write +  "] = " + item);
        return item;
    }
    
    public abstract int type();

    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        if (o == null) {
            return false;
        }
        if (getClass() != o.getClass()) {
            return false;
        }
        Ring r = (Ring) o;
        return (this.size == r.size);
    //    return ((this.buffer == r.buffer)
    //         && (this.read   == r.read)
    //         && (this.write  == r.write)
    //         && (this.size   == r.size));
    }

    public int hashCode() {
        int result = 17;
        result = 37 * result + read;
        result = 37 * result + write;
        result = 37 * result + size;
        return result;
    }

    public String toString() {
        return "Ring[rd=" + read + ", wr=" + write + ", sz=" + size + "]";
    }
}
