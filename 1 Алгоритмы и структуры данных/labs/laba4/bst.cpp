#include <iostream>
using namespace std;

// Структура узла для бинарного дерева поиска
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Класс для представления бинарного дерева поиска
class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Вставка узла
    void insert(int data) {
        root = insert(root, data);
    }

    // Удаление узла
    void remove(int data) {
        root = remove(root, data);
    }

    // Поиск узла
    Node* search(int data) {
        return search(root, data);
    }

    // Обход в порядке возрастания
    void inorderTraversal() {
        inorder(root);
    }

    // Вспомогательная рекурсивная функция для вставки узла
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            return createNode(data);
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else if (data > root->data) {
            root->right = insert(root->right, data);
        }
        return root;
    }

    // Вспомогательная рекурсивная функция для удаления узла
    Node* remove(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }
        if (data < root->data) {
            root->left = remove(root->left, data);
        } else if (data > root->data) {
            root->right = remove(root->right, data);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
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

    // Вспомогательная рекурсивная функция для поиска узла
    Node* search(Node* root, int key) {
        if (root == nullptr || root->data == key) {
            return root;
        }
        if (root->data < key) {
            return search(root->right, key);
        }
        return search(root->left, key);
    }

    // Вспомогательная рекурсивная функция для обхода в порядке возрастания
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    // Вспомогательная функция для поиска минимального узла
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Вспомогательная функция для создания нового узла
    Node* createNode(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }
};


int main() {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Обход в порядке возрастания: ";
    bst.inorderTraversal();
    cout << endl;

    cout << "Поиск узла 40: ";
    Node* foundNode = bst.search(40);
    if (foundNode != nullptr) {
        cout << "Найден" << endl;
    } else {
        cout << "Не найден" << endl;
    }

    cout << "Удаление узла 30" << endl;
    bst.remove(30);

    cout << "Обход в порядке возрастания: ";
    bst.inorderTraversal();
    cout << endl;

    return 0;
}
