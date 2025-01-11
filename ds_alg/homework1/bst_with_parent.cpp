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
        std::cout<<std::endl;
    }

    void print(Node* node) {
        if (node == nullptr) {
            return;
        }

        print(node->left);
        std::cout << node->value << " ";
        print(node->right);
    }

    Node* search(int value) {
        return search(root, value);
    }

    Node* search(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
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

    Node* remove(int value) {
        return remove(root, value);
    }

    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* right = node->right;
                Node* parent = node->parent;
                if (right) right->parent = parent;
                delete node;
                return right;
            } else if (node->right == nullptr) {
                Node* left = node->left;
                Node* parent = node->parent;
                if(left) left->parent = parent;
                delete node;
                return left;
            } else {
                Node* minRight = min(node->right);
                node->value = minRight->value;
                node->right = remove(node->right, minRight->value);
            }
        }

        return node;
    }

    void horizontal_flip_rec() {
        horizontal_flip_rec(root);
    }

    void horizontal_flip_rec(Node* node) {
        if(node == nullptr || node->left == node->right) return;

        Node* tmp = node->right;
        node->right = node->left;
        node->left = tmp;
        
        horizontal_flip_rec(node->left);
        horizontal_flip_rec(node->right);
    }

    void horizontal_flip_iter() {
        horizontal_flip_iter(root);
    }

    void horizontal_flip_iter(Node* node) {
        std::queue<Node*> q{{node}};
        while(!q.empty()) {
            Node* root = q.front();
            q.pop();

            Node* tmp = root->left;
            root->left = root->right;
            root->right = tmp;

            if (root->left != nullptr) q.emplace(root->left);
            if (root->right != nullptr) q.emplace(root->right);
        }
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
};


bool is_bst(Node* root, int min=std::numeric_limits<int>::min(), int max=std::numeric_limits<int>::max()) {
    if (root == nullptr) {
        return true;
    }

    if (root->value < min || root->value > max) {
        return false;
    }

    return is_bst(root->left, min, root->value) && is_bst(root->right, root->value, max);
}

bool is_flipped_bst(Node* root, int min=std::numeric_limits<int>::min(), int max=std::numeric_limits<int>::max()) {
    if (root == nullptr) {
        return true;
    }

    if (root->value < min || root->value > max) {
        return false;
    }

    return is_flipped_bst(root->left, root->value, max) && is_flipped_bst(root->right, min, root->value);
}


int main() {
    // BST bst;
    // bst.insert(5);
    // bst.insert(3);
    // bst.insert(7);
    // bst.insert(2);
    // bst.insert(4);
    // bst.insert(6);
    // bst.insert(8);

    // bst.print();
    // std::cout << std::endl;

    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(7);
    root->left->left = new Node(2);
    root->left->right = new Node(4);
    
    BST bst{root};

    std::cout << is_bst(root) << std::endl;

    bst.print();

    bst.horizontal_flip_rec();
    // bst.horizontal_flip_iter();

    bst.print();
    std::cout << is_bst(root) << std::endl;
    std::cout << is_flipped_bst(root) << std::endl;

    return 0;
}
