import java.util.*;

public class VecTest {


    public static void main(String[] args)
    {
        //List<Integer> v = new ArrayList<Integer>();
        Vector<Integer> v = new Vector<Integer>();
        System.out.println("hello");
        v.add(new Integer(1));
        v.add(new Integer(2));
        v.add(new Integer(3));
        v.add(new Integer(4));
        
        Enumeration vEnum = v.elements();
        System.out.println("\nElements in vector:");
        while(vEnum.hasMoreElements())
            System.out.print(vEnum.nextElement() + " ");
        System.out.println();

    }
}
