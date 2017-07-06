import java.util.*;
import java.io.*;

class Prefix {
    public Vector pref;
    Prefix(int n, String str) {
        pref = new Vector();
        for (int i = 0; i < n; ++i)
            pref.addElement(str);
    }
    Prefix(Prefix p) {
        pref = (Vector) p.pref.clone();
    }
    public boolean equals(Object o) {
        Prefix p = (Prefix) o;
        for (int i = 0; i < pref.zize(); ++i) {
            if (!pref.elementAt(i).equals(p.pref.elementAt(i)))
                return false;
        }
        return true;
    }
}

class Chain {
    static final int NPREF = 2;
    static final String NONWORD = "\n";
    Hashtable statetab = new Hashtable();
    Prefix prefix = new Prefix(NPREF, NONWORD);
    Random rand = new Random();
    void add(String word) {
        Vector suf = (Vector) statetab.get(prefix);
        if (suf == null) {
            suf = new Vector();
            statetab.put(new Prefix(prefix), suf);
        }
        suf.addElement(word);
        prefix.pref.removeElementAt(0);
        prefix.pref.addElement(word);
    }

    void build(InputStream in) {
        StreamTokenizer st = new StreamTokenizer(in);
        try {
            st.resetSyntax();
            st.wordChars(0, Character.MAX_VALUE);
            st.whitespaceChars(0, ' ');
            while (st.nextToken() != st.TT_EOF)
                add(st.sval);
            add(NONWORD);
        } catch (IOException e) {
            System.out.println(e);
        }
    }
    void generate(int nwords) {}
}


public class Markov {
    static final int MAXGEN = 10000;
    public static void main(String[] args) {
        Chain chain = new Chain();
        int nwords = MAXGEN;
        chain.build(System.in);
        chain.generate(nwords);
        System.out.println("hello, world");
    }
}
