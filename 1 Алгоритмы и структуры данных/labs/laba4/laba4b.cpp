#include <iostream>
/*
добавить
удалить
проверить есть ли такой номер
минимальный >n номер компанты
максимаьный <n номер комнаты
*/
struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {

private:
    Node* root;

public:
    Tree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    Node* search(int data) {
        return search(root, data);
    }

    int findNextLarger(int data) {
        return findNextLarger(root, data);
    }

    int findPreviousSmaller(int data) {
        return findPreviousSmaller(root, data);
    }


    Node* createNode(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            return createNode(data);
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        }
        else if (data > root->data) {
            root->right = insert(root->right, data);
        }
        return root;
    }

    Node* minValueNode(Node* root) {
        Node* current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* remove(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }
        if (data < root->data) {
            root->left = remove(root->left, data);
        }
        else if (data > root->data) {
            root->right = remove(root->right, data);
        }
        else if (data == root->data) {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
        return root;
    }

    Node* search(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }
        if (root->data < data) {
            return search(root->right, data);
        }
        if (root->data > data) {
            return search(root->left, data);
        }
        return root;
    }

    int findNextLarger(Node* root, int data) {
        int res = -1;
        while (root != nullptr) {
            if (root->data > data) {
                res = root->data;
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return res;
    }

    int findPreviousSmaller(Node* root, int data) {
        int res = -1;
        while (root != nullptr) {
            if (root->data < data) {
                res = root->data;
                root = root->right;
            }
            else {
                root = root->left;
            }
        }
        return res;
    }
};


int main() {
    int n, value;

    Tree bst;
    while (std::cin >> n >> value) {
        if (n == 0)
        {
            bst.insert(value);
        }
        else if (n == 1)
        {
            bst.remove(value);
        }
        else if (n == 2)
        {
            if (bst.search(value)) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
        else if (n == 3)
        {
            int min = bst.findNextLarger(value);
            if (min == -1) {
                std::cout << "none\n";
            }
            else {
                std::cout << min << '\n';
            }
        }
        else if (n == 4)
        {
            int max = bst.findPreviousSmaller(value);
            if (max == -1) {
                std::cout << "none\n";
            }
            else {
                std::cout << max << '\n';
            }
        }
    }
    return 0;
}
