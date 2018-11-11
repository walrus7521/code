import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
 
import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections; 
import java.util.Map; 
import java.util.HashMap; 
import java.util.Set;
import java.util.Stack;
 
import org.antlr.v4.misc.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.MultiMap;
import org.antlr.v4.runtime.misc.OrderedHashSet;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import org.stringtemplate.v4.ST;


public class core {

    public static final double PI = 3.141;

    // single instance
    static Map<String, Integer> msi = new HashMap<String, Integer>();
    static Map<String, String> omsi = new OrderedHashMap<String, String>();
    static Stack<Integer> stack = new Stack<Integer>();
    static List<Map<String, String>> lmss = new ArrayList<Map<String, String>>();
    static List<String> ls = new LinkedList<String>();
    static Set<String> ss = new OrderedHashSet<String>();
    static MultiMap<String, String> mmss = new MultiMap<String, String>();

    public static void main(String[] args) throws Exception {
        String inFile = null;
        if (args.length > 0) inFile = args[0];
        InputStream is = System.in;
        OutputStream os = System.out;
        if (inFile != null) is = new FileInputStream(inFile);
        char c;
        byte[] buf = new byte[256];
        String line;
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        int i = 0;
        while ((line = reader.readLine()) != null) {
            //System.out.println(line);
            msi.put(line, i++);
            omsi.put(line, "dude"+i);
            stack.push(i);
            ls.add(line);
            mmss.map(line, "dude"+i);
        }
        lmss.add(omsi);

        for (String s : msi.keySet()) {
            System.out.print(msi.get(s));
            System.out.println(s);
        }

        for (String s : omsi.keySet()) {
            System.out.println(omsi.get(s));
        }

        while (!stack.empty()) {
            System.out.println(stack.pop());
        }

        StringBuilder sbuf = new StringBuilder();
        sbuf.append("\n");
        for (String liner : ls) {
            System.out.print("> ");
            System.out.println(liner);
            sbuf.append(liner);
        }

        String out = String.format("%d lines\n", i);
        System.out.println(out);
        System.out.println(sbuf.toString());

        for (String ss : mmss.keySet()) {
            System.out.print("mm> ");
            System.out.print(ss);
            System.out.println(mmss.get(ss));
        }
    }
}
