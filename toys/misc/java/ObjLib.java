import java.util.*;

public class ObjLib {

    static void stack_demo() {
        Stack<String> stack = new Stack<>();
        stack.push("alpha");
        stack.push("beta");
        System.out.println( "stack = " + stack );
    }

    static void array_list_demo() {
        List<String> list = new ArrayList<>();
        list.add("alpha");
        list.add("beta");
        System.out.println( "array list = " + list );
        list.remove("beta");
        list.clear();
    }

    static void linked_list_demo() {
        List<String> list = new LinkedList<>();
        list.add("alpha");
        list.add("beta");
        System.out.println( "linked list = " + list );
        list.remove("beta");
        list.clear();
    }

    static void hash_map_demo() {
        Map map = new HashMap();
        map.put("alpha", 3);
        map.put("beta", 7);
        System.out.println( "hash map = " + map );        
    }

    static void hash_table_demo() {
        Map map = new Hashtable();
        map.put("alpha", 3);
        map.put("beta", 7);
        System.out.println( "hash table = " + map );        
    }

    static void tree_map_demo() {
        SortedMap map = new TreeMap();
        map.put("alpha", 3);
        map.put("beta", 7);
        System.out.println( "tree map = " + map );        
    }

    static void hash_set_demo() {
        Set set = new HashSet();
        set.add("alpha");
        set.add("beta");
        System.out.println( "hash set = " + set );        
    }

    public static void main(String[] args) {
        System.out.println("demo of generic containers..");

        array_list_demo();
        linked_list_demo();
        stack_demo();
        hash_map_demo();
        hash_table_demo();
        tree_map_demo();
        hash_set_demo();

    }
};
