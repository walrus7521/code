public class btree {
    public final int MAX_BRANCH = 4;
    public final int MIN_BRANCH = 2;
    public class btree_entry {
        char key;
    };
    public class btree_node {
        int count;
        btree_entry[] entry;
        btree_node[] branch;
    };
    btree() {
    }
    btree_node btree_create() {
        int i;
        btree_node root = new btree_node();
        root.count = 0;
        root.branch = new btree_node[MAX_BRANCH+1]; 
        for (i = 0; i < MAX_BRANCH; i++)
            root.branch[i] = null;
        return root;
    }
    void btree_find(char val) {
    }
    btree_node btree_insert() {
        return null;
    }
    boolean empty() {
       return true;
    }
    void show_btree() {
    }
}
