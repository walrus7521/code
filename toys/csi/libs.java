import java.util.*;

// Array, Arraylist, Hashtable, HashMap, HashSet, Node, NodeList, TreeNode, and TreeMap

public class libs
{
    public static void main (String[] args)
    {
        List<String> l = new ArrayList<String>(5);
        l.add("geek");
        l.add("code");
        System.out.println(l);

        Map<String,Integer> hsi = new HashMap<String,Integer>();
        hsi.put("dude", 42);
        hsi.put("sup", 17);
        System.out.println(hsi);

        Vector<Integer> queue=new Vector<Integer>();
        queue.add(1);
        queue.add(2);
        queue.add(3);
        System.out.println(queue);

        int top = 0;
        ArrayList<Integer> stack = new ArrayList<Integer> ();
        stack.add(top++, 6);
        stack.add(top++, 7);
        stack.add(top++, 8);
        while (top > 0) { System.out.println(stack.remove(--top)); };
        
        Set<String> set = new HashSet<String>();
        set.add("geek");
        set.add("geek");
        set.add("geek");
        set.add("nerd");
        set.add("nerd");
        System.out.println(set);
    }
}
