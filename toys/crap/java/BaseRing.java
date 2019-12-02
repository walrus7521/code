interface BaseRing {

    public boolean full();
    public boolean empty();
    public void put_front(int item);
    public int get_back();
    public int get_front();
    public abstract int type();
    public boolean equals(Object o);
    public int hashCode();
    public String toString();

}
