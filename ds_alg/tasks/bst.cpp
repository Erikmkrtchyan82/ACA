#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>

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


    Node* inorder_minus() {
        return inorder_minus(root);
    }

    Node* inorder_minus(Node* node) {
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

Node* batch_construction(
    std::vector<int>::iterator begin,
    std::vector<int>::iterator end,
    Node* node
) {
    int size = std::distance(begin, end);
    if (size == 0) return nullptr;
    auto mid = begin + size/2;
    // bst.insert(*mid);
    node = new Node(*mid);

    if (size == 1) return node;

    node->left = batch_construction(begin, mid, node);
    node->right = batch_construction(mid + 1, end, node);
    return node;
}

Node* batch_construction(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
    Node* node = batch_construction(arr.begin(), arr.end(), node);
    return node;
}

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

void test_bst_create() {
    BST bst = get_bst();
    bst.print();
    std::cout << std::endl;
}

void test_bst_check() {
    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(7);
    root->left->left = new Node(2);
    root->left->right = new Node(4);

    BST bst{root};

    std::cout << is_bst(root) << std::endl;

    bst.print();
}

void test_flip() {
    BST bst = get_bst();
    bst.horizontal_flip_rec();
    bst.horizontal_flip_iter();

    bst.print();
    std::cout << is_bst(bst.root) << std::endl;
    std::cout << is_flipped_bst(bst.root) << std::endl;
}

void test_inorder_minus() {
    BST bst = get_bst();

    bst.print();

    Node* max = bst.max();

    while (max != nullptr) {
        std::cout << max->value << std::endl;
        max = bst.inorder_minus(max);
    }
}

void test_batch_construct() {
    std::vector vec{12, 8, 10, 22, 15};
    BST bst{batch_construction(vec)};
    bst.print();
    std::cout << is_bst(bst.root) << std::endl;
}



int main() {
    test_batch_construct();
    return 0;
}
