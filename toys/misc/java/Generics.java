import java.util.*;


class Mouse {}
class Bear {}

class Trap< T > {
    T trapped;
    List<T> trappedList; // = new ArrayList<>();;
    Trap() {
        System.out.println("trap created");
        trappedList = new ArrayList<T>();
    }

    public void setType( Class<T> type ) {
        System.out.println("setting type to: " + type.toString());
    }

    public void snare( T trapped ) { 
        this.trapped = trapped; 
        trappedList.add(trapped);
        System.out.println("snared");
    }

    public T release() { 
        System.out.println("released");
        return trapped; 
    }

    public void show() {
        //for (t : trappedList) 
        //    System.out.println("t");
    }
}

interface Sling< T > {
    void slung();
}

class AdjustableTrap<T> extends Trap<T> {
    int size;
    AdjustableTrap() {
        System.out.println("adjustable trap created");
    }
    public void setSize(int i) {
        size = i;
        System.out.println("size is now: " + size);
    }
}

//class TrapList<T extends Trap & Sling> {
class TrapList<T extends Trap & Sling> {
    void slung() {}
}

class ExceptionTester<T extends Throwable> {
    public void test(T exception) throws T {
        throw exception;
    }
}

public class Generics {

    // wildcard capture
    <T> Set<T> listToSet( List<T> list ) {
        Set<T> set = new HashSet<T>();
        set.addAll(list);
        return set;
    }

    <T> List<T> swapGeneric( List<T> list ) {
        T tmp = list.get(0);
        list.set(0, list.get(1));
        list.set(1, tmp);
        return list;
    }

    // generic method
    <T, V> T cache1( T entry1 , V entry2) {
        return entry1;
    }
    
    <T, V> V cache2( T entry1 , V entry2) {
        return entry2;
    }
    
    <T> Trap<T> makeTrap() { return new Trap<T>(); }

    void useCache() {
        int dude = 77;
        String the_dude = "the duderino";
        int rc = cache1(dude, the_dude);
        String src = cache2(dude, the_dude);
        System.out.println("cache1 dude: " + rc);
        System.out.println("cache2 dude: " + src);
    }

    static void useWild() {
        List<? extends String> readable_str_list;
        List<? super String> writable_str_list;
        List<?> gen_str_list;
        readable_str_list = new ArrayList<String>();
        writable_str_list = new ArrayList<String>();
        //gen_str_list = writable_str_list;
        //readable_str_list = gen_str_list;
        writable_str_list.add("sup");
        //String s;
        //s = gen_str_list.get(0); System.out.println(s);
        //ls.add("add");
        //ls.add("dude");
        //String s;
        //s = ls.get(0); System.out.println(s);
        //s = ls.get(1); System.out.println(s);
        //s = ls.get(2); System.out.println(s);
    }

    static void useException() {
        try {
            new ExceptionTester<ClassNotFoundException>().test(
                new ClassNotFoundException() );
        } catch (ClassNotFoundException e) {
            System.out.println("dude! " + e.toString());
        }
    }

     static void useTrap() {
        Trap<Mouse> mouseTrap = new Trap<>();
        mouseTrap.snare( new Mouse() );
        mouseTrap.setType(Mouse.class);
        Mouse mouse = mouseTrap.release();

        AdjustableTrap<Bear> adjBearTrap = new AdjustableTrap<>();
        adjBearTrap.setSize(6);
        Bear bear = adjBearTrap.release();
        adjBearTrap.setType(Bear.class);
        adjBearTrap.snare(bear);

    }

    static void useList() {
        List<String> listOfStrings = new ArrayList<>();
        listOfStrings.add("eureka!");
        String s = listOfStrings.get(0);
        System.out.println(s);
    }

    static void useMap() {
        Map<String, Integer> si = new HashMap<>();
        Integer Id = 777;
        String Name = "Bart";
        si.put(Name, Id);

        Integer id = si.get(Name);
        System.out.println(id);
    }

    public static void main(String[] args) {
        Doit d = new Doit();
        d.doit();
        //useWild();
        //useException();
        //useList();
        //useMap();
        //useTrap();
    }


}

class Doit {

    Generics g = new Generics();
    
    //List<?> swapper( List<?> list ) {
    List<String> swapper( List<String> list ) {
        return g.swapGeneric(list);
    }

    int doit() {
        g.useCache();

        Trap<Mouse> mouseTrap = g.makeTrap();
        mouseTrap.snare( new Mouse() );
        mouseTrap.setType(Mouse.class);
        Mouse mouse = mouseTrap.release();

        List<? super String> list = new ArrayList<String>();
        list.add("dude");
        list.add("sup");
        list.add("homi");
        Set<?> set = g.listToSet(list);
        String s = "duderino";
        if (set.contains(s)) {
            System.out.println("yes - set contains " + s);
        } else {
            System.out.println("no - set does not contain " + s);
        }

        List<String> lStr = new ArrayList<>();
        lStr.add("alpha");
        lStr.add("beta");
        s = lStr.get(0); System.out.println(s);
        s = lStr.get(1); System.out.println(s);
        List<String> swap;
        //swap = g.swapGeneric(lStr);
        swap = swapper(lStr);
        s = swap.get(0); System.out.println(s);
        s = swap.get(1); System.out.println(s);

        System.out.println("let's iterate..");
        Iterator i = swap.iterator();
        while (i.hasNext()) {
            Object o = i.next();
            System.out.println(o.toString());
        }

        return 0;
    }
}
