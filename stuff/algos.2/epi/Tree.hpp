template <typename T>
class BinaryTreeNode {
public:
    BinaryTreeNode<T>() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    };
    ~BinaryTreeNode<T>() {
        delete left;
        delete right;
        delete parent;
    }
//private:
    T key_value, max, min;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    BinaryTreeNode<T> *parent;
};

template <typename T>
class BinaryTree {
public:
    BinaryTree<T>() { root = nullptr; }
    ~BinaryTree<T>() { destroy_tree(); }
    void destroy_tree() { destroy_tree(root); }
    void destroy_tree(BinaryTreeNode<T> *tree) { 
        if (tree != nullptr) {
            destroy_tree(tree->left);
            destroy_tree(tree->right);
            delete tree;
        }
    }
    void insert(T key) {
        if(root != nullptr) {
            insert(key, root);
        } else {
            root = new BinaryTreeNode<T>();
            root->key_value = key;
            root->left = nullptr;
            root->right = nullptr;
        }        
    }
    BinaryTreeNode<T> *search(T key) {
        return search(root, key);
    }

    void show() {
        show(root);
    }
    BinaryTreeNode<T> *get_root() {
        return this->root;
    }
private:
    BinaryTreeNode<T> *search(BinaryTreeNode<T> *tree, T key) {
        if(tree != nullptr) {
            if(key==tree->key_value)
                return tree;
            if(key<tree->key_value)
                return search(tree->left, key);
            else
                return search(tree->right, key);
        }
        else return nullptr;

    }
    void insert(T key, BinaryTreeNode<T> *leaf) {
        if(key < leaf->key_value) {
            if(leaf->left != nullptr) {
                insert(key, leaf->left);
            } else {
                leaf->left = new BinaryTreeNode<T>();
                leaf->left->key_value = key;
                leaf->left->left = nullptr;    //Sets the left child of the child node to null
                leaf->left->right = nullptr;   //Sets the right child of the child node to null
            }  
        } else 
        if(key >= leaf->key_value) {
            if(leaf->right != nullptr) {
                insert(key, leaf->right);
            } else {
                leaf->right = new BinaryTreeNode<T>();
                leaf->right->key_value = key;
                leaf->right->left = nullptr;  //Sets the left child of the child node to null
                leaf->right->right = nullptr; //Sets the right child of the child node to null
            }
        }    
    }
    void show(BinaryTreeNode<T> *tree) {
        if (tree != nullptr) {
            show(tree->left);
            std::cout << tree->key_value << std::endl;
            show(tree->right);
        }
    }

    BinaryTreeNode<T> *root;
};



