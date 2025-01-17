#include <iostream>
#include <limits>
#include <queue>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value, Node* parent = nullptr) : value(value), left(nullptr), right(nullptr), parent(parent) {}
};

class BST {
public:
    Node* root;
    BST(Node* r=nullptr) : root{r} {}

    void insert(int value) {
        root = insert(root, value);
    }

    Node* insert(Node* node, int value, Node* parent = nullptr) {
        if (node == nullptr) {
            return new Node(value, parent);
        }

        if (value < node->value) {
            node->left = insert(node->left, value, node);
        } else {
            node->right = insert(node->right, value, node);
        }

        return node;
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    void print(Node* node) {
        if (node == nullptr) {
            return;
        }

        print(node->left);
        std::cout << node->value << " ";
        print(node->right);
    }

    Node* min() {
        return min(root);
    }

    Node* min(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left == nullptr) {
            return node;
        }

        return min(node->left);
    }

    Node* max() {
        return max(root);
    }

    Node* max(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->right == nullptr) {
            return node;
        }

        return max(node->right);
    }
 
    Node* inorder_decrement() {
        return inorder_decrement(root);
    }

    Node* inorder_decrement(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left != nullptr) {
            return max(node->left);
        }

        while (node->parent != nullptr && node == node->parent->left)
            node = node->parent;

        return node->parent;
    }

    Node* inorder_increment() {
        return inorder_increment(root);
    }

    Node* inorder_increment(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->right != nullptr) {
            return min(node->right);
        }

        while (node->parent != nullptr && node == node->parent->right)
            node = node->parent;

        return node->parent;
    }

    Node* preorder_increment() {
        return preorder_increment(root);
    }

    Node* preorder_increment(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left != nullptr) {
            return node->left;
        }

        if (node->right != nullptr) {
            return node->right;
        }

        while (node->parent != nullptr && (node == node->parent->right || node->parent->right == nullptr))
            node = node->parent;
        
        if (node->parent == nullptr) {
            return nullptr;
        }

        return node->parent->right;
    }

    Node* preorder_decrement() {
        return preorder_decrement(root);
    }

    Node* preorder_decrement(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->parent == nullptr) {
            return nullptr;
        }

        if (node == node->parent->right && node->parent->left != nullptr) {
            return max(node->parent->left);
        }

        return node->parent;
    }

    double balanceness() {
        return balanceness(root);
    }

    double balanceness(Node* node) {
        if (node == nullptr) {
            return 0.0;
        }

        int minDepth = _min_depth(node);
        int maxDepth = _max_depth(node);

        return (double)minDepth / maxDepth;
    }

    ~BST() {
        deleteTree(root);
    }

private:
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    int _min_depth(Node* node) {
        if (node == nullptr) {
            return std::numeric_limits<int>::max();
        }

        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        return 1 + std::min(_min_depth(node->left), _min_depth(node->right));
    }

    int _max_depth(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + std::max(_max_depth(node->left), _max_depth(node->right));
    }
};


BST get_bst() {
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    return bst;
}

void test_preorder_traversal() {
    BST bst = get_bst();
    bst.print();
    std::cout << std::endl;

    Node* max = bst.max();

    while (max != nullptr) {
        std::cout << max->value << " ";
        max = bst.preorder_decrement(max);
    }
    std::cout<< std::endl;
}

int main() {
    BST bst = get_bst();
    std::cout << bst.balanceness() <<std::endl;
    test_preorder_traversal();

    return 0;
}
