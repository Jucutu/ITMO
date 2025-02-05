#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int y;
std::string SearchTreeBuilder;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}

    void inOrder() {
        if (left != nullptr) {
            left->inOrder();
        }
        SearchTreeBuilder += std::to_string(data) + " ";
        if (right != nullptr) {
            right->inOrder();
        }
    }

    void solveInOrder(class SearchTree* tree);
};

class SearchTree {
public:
    Node* root;
    Node* current;

    SearchTree() : root(nullptr), current(nullptr) {}

    void inOrder() {
        if (root == nullptr) {
            return;
        }
        root->inOrder();
        if (!SearchTreeBuilder.empty()) {
            SearchTreeBuilder.pop_back();
        }
        SearchTreeBuilder += "\n";
    }

    void solve(SearchTree* other) {
        if (other->root == nullptr) {
            other->root = root;
            other->current = root;
            root = nullptr;
            return;
        }
        preSolve();
        if (root != nullptr) {
            root->solveInOrder(other);
        }
        root = nullptr;
    }

    void preSolve() {
        current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
    }

    void solveInsert(Node* value) {
        bool find = false;
        Node* end = current;
        while (current->parent != nullptr && current->parent->data <= value->data) {
            if (current->parent->left == current) {
                end = current->parent;
            }
            if (current->data == value->data) {
                find = true;
                break;
            }
            current = current->parent;
        }
        if (!find) {
            current = end;
            insertByNode(value->data);
        }
    }

    void insertByNode(int data) {
        Node* parent = nullptr;
        bool isRight = false;
        while (current != nullptr) {
            parent = current;
            if (data > current->data) {
                current = current->right;
                isRight = true;
            } else if (data == current->data) {
                return;
            } else {
                current = current->left;
                isRight = false;
            }
        }
        current = new Node(data);
        current->parent = parent;
        if (isRight) {
            parent->right = current;
        } else {
            parent->left = current;
        }
    }

    Node* getNext(int value) {
        Node* current = root;
        Node* successor = nullptr;
        while (current != nullptr) {
            if (current->data > value) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return successor;
    }

    void insert(int data) {
        if (root == nullptr) {
            root = new Node(data);
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        bool isRight = false;
        while (current != nullptr) {
            parent = current;
            if (data > current->data) {
                current = current->right;
                isRight = true;
            } else if (data == current->data) {
                return;
            } else {
                current = current->left;
                isRight = false;
            }
        }
        this->current = new Node(data);
        this->current->parent = parent;
        if (isRight) {
            parent->right = this->current;
        } else {
            parent->left = this->current;
        }
    }

    Node* getNode(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return current;
            } else if (value > current->data) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return nullptr;
    }

    void deleteChild(Node* parent, Node* child) {
        if (parent->left == child) {
            parent->left = nullptr;
        } else if (parent->right == child) {
            parent->right = nullptr;
        }
    }

    void deleteNode(int value, Node* deletable = nullptr) {
        if (deletable == nullptr) {
            deletable = getNode(value);
        }
        if (deletable != nullptr) {
            Node* parent = deletable->parent;
            if (parent != nullptr) {
                if (deletable->left == nullptr && deletable->right == nullptr) {
                    deleteChild(parent, deletable);
                } else if (deletable->left != nullptr && deletable->right == nullptr) {
                    Node* child = deletable->left;
                    child->parent = parent;
                    if (deletable == parent->left) {
                        parent->left = child;
                    } else {
                        parent->right = child;
                    }
                } else if (deletable->left == nullptr) {
                    Node* child = deletable->right;
                    child->parent = parent;
                    if (deletable == parent->left) {
                        parent->left = child;
                    } else {
                        parent->right = child;
                    }
                } else {
                    Node* next = getNext(deletable->data);
                    int t = deletable->data;
                    deletable->data = next->data;
                    next->data = t;
                    deleteNode(next->data, next);
                }
            } else {
                if (deletable->left == nullptr && deletable->right == nullptr) {
                    root = nullptr;
                } else if (deletable->left != nullptr && deletable->right == nullptr) {
                    root = root->left;
                    root->parent = nullptr;
                } else if (deletable->left == nullptr) {
                    root = root->right;
                    root->parent = nullptr;
                } else {
                    Node* next = getNext(deletable->data);
                    int t = deletable->data;
                    deletable->data = next->data;
                    next->data = t;
                    deleteNode(next->data, next);
                }
            }
        }
    }
};

void Node::solveInOrder(SearchTree* tree) {
    if (left != nullptr) {
        left->solveInOrder(tree);
    }
    tree->solveInsert(this);
    if (right != nullptr) {
        right->solveInOrder(tree);
    }
}

int main() {
    SearchTree tree0, tree1;
    std::string line;
    std::getline(std::cin, line);
    int q = std::stoi(line);
    y = q;

    for (int i = 0; i < q; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        int command = std::stoi(tokens[0]);
        if (command == 2) {
            tree1.solve(&tree0);
            tree0.inOrder();
        } else {
            int number = std::stoi(tokens[1]);
            int data = std::stoi(tokens[2]);
            if (command == 0) {
                if (number == 0) {
                    tree0.insert(data);
                } else {
                    tree1.insert(data);
                }
            } else {
                if (number == 0) {
                    tree0.deleteNode(data);
                } else {
                    tree1.deleteNode(data);
                }
            }
        }
    }
    std::cout << SearchTreeBuilder;
    return 0;
}

