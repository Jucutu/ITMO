#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    std::string key;
    int data;
    bool sentBy1 = false, sentBy2 = false, sentBy3 = false;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(std::string k) : key{k} {}
};

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void fixHeight(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

Node* rightRotate(Node* node) {
    Node* leftChild = node->left;
    if (leftChild == nullptr) {
        return node;
    }
    Node* y = leftChild->right;

    leftChild->right = node;
    node->left = y;

    fixHeight(node);
    fixHeight(leftChild);

    return leftChild;
}

Node* leftRotate(Node* node) {
    Node* rightChild = node->right;
    if (rightChild == nullptr) {
        return node;
    }
    Node* y = rightChild->left;

    rightChild->left = node;
    node->right = y;

    fixHeight(node);
    fixHeight(rightChild);

    return y;
}

Node* bigRight(Node* node) {
  leftRotate(node->left);
  return rightRotate(node);
}

Node* bigLeft(Node* node) {
  rightRotate(node->right);
  return leftRotate(node);
}

Node* insert(Node* node, const std::string& key, int student) {
    if (node == nullptr) {
        node = new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, student);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, student);
    }
    else {
        if (student == 1) node->sentBy1 = true;
        if (student == 2) node->sentBy2 = true;
        if (student == 3) node->sentBy3 = true;
        return node;
    }

    fixHeight(node);

    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void calculateScores(Node* root, int& score1, int& score2, int& score3) {
    if (root == nullptr) {
        return;
    }

    int sentCount = (root->sentBy1 ? 1 : 0) + (root->sentBy2 ? 1 : 0) + (root->sentBy3 ? 1 : 0);

    if (sentCount == 1) {
        if (root->sentBy1) score1 += 3;
        if (root->sentBy2) score2 += 3;
        if (root->sentBy3) score3 += 3;
    }
    else if (sentCount == 2) {
        if (root->sentBy1) score1 += 1;
        if (root->sentBy2) score2 += 1;
        if (root->sentBy3) score3 += 1;
    }

    calculateScores(root->left, score1, score2, score3);
    calculateScores(root->right, score1, score2, score3);
}

int main() {
    int n;
    std::cin >> n;

    Node* root = nullptr;
    std::vector<std::string> student1(n), student2(n), student3(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> student1[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> student2[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> student3[i];
    }

    for (int i = 0; i < n; ++i) {
        root = insert(root, student1[i], 1);
        root = insert(root, student2[i], 2);
        root = insert(root, student3[i], 3);
    }

    int score1 = 0, score2 = 0, score3 = 0;
    calculateScores(root, score1, score2, score3);

    std::cout << score1 << " " << score2 << " " << score3;
    return 0;
}
