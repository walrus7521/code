using System;


struct Seq : ISeq
{
    private readonly int b, k, n;
    public Seq(int m, int n) : this(m, 1, n-m+1){}

}

private class SeqEnumerator : IEnumerator<int>
{
    private readonly Seq seq;
    private int i;
    public SeqEnumerator(Seq seq) { this.seq = seq; Reset(); }
    public int Current
    {
        get
        {
            if (0 <= i && i < seq.n)
            {
                return seq.b + seq.k * i;
            }
            else
            {
                throw InvalidOperatorException();
            }
        }
    }
    Object SC.IEnumerator.Current { get { return Current; } }
    public bool MoveNext()
    {
        return ++i < seq.n;
    }
    public void Reset() { i = -1; }
    public void Dispose() {}
}

