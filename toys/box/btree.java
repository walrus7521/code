

public class btree {

    public class Key {
        char key;
    };

    public class Value {
        char value;
    };
    
    public class pair {
        Key key;
        Value value;
    };

    public class btree_node {
        int count;
        pair[]       entry;
        btree_node[] branch;
    };
    
    public final int MAX_BRANCH = 4;
    public final int MIN_BRANCH = 2;
    
    public class btree_entry {
        char key;
    };

    private btree_node root;

    btree() {
        System.out.println("btree constructor...\n");
        root = new btree_node();
        root.entry = new pair[MAX_BRANCH+1];
        root.count = 0;
        root.branch = new btree_node[MAX_BRANCH+1]; 
        for (int i = 0; i < MAX_BRANCH; i++)
            root.branch[i] = null;
    }


    private btree_node btree_search(Key target, btree_node root, Integer intra_node_target_pos) {
        return null;
    }

    private int search_node(Key target, btree_node current, Integer pos) {
        return 0;
    }

    private void btree_push_in(pair medentry, btree_node medright, btree_node current, Integer pos) {
    }

    private void btree_split(pair medentry, btree_node medright, btree_node current, Integer pos, 
                pair newmedian, btree_node newright) {
    }

    
    private int btree_push_down() {
        return 0;
    }


    public void btree_find(char val) {
    }

    public int btree_insert() {
        return 0;
    }

    public boolean empty() {
       return true;
    }

    public void show_btree() {
    }

    public static void main(String[] args) {
        System.out.println("enter btree test code...\n");
        btree bt = new btree();
    }
}
