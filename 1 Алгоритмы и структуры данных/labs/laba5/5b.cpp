#include <iostream>
#include <queue>
#include <vector>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int delta = 0;
    int height = 0;
    int placee = 0;
    Node(int data) : data {data} {}
};

Node* postOrder(Node *node) {
    if (node == nullptr)
        return nullptr;

    Node* leftChild = postOrder(node->left);
    Node* rightChild = postOrder(node->right);
    int l = leftChild ? leftChild->height : 0;
    int r = rightChild ? rightChild->height : 0;
    node->height = std::max(l, r) + 1;
    node->delta = r - l;
    return node;
}

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

Node* rightRotate(Node* a) {
    Node *b = a->left;

    a->left = b->right;
    b->right = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node* leftRotate(Node* a) {
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node* bigRight(Node* node) {
  leftRotate(node->left);
  return rightRotate(node);
}

Node* bigLeft(Node* node) {
  rightRotate(node->right);
  return leftRotate(node);
}

Node* turnLeft(Node* a) {
    if (a->delta == 2) {
        if (a->right->delta < 0) {
            a->right = rightRotate(a->right);
            return leftRotate(a);
        }
        else {
            return leftRotate(a);
        }
    }
    return a;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Node*> nodeArray(n, nullptr);
    std::vector<int> mas_left(n);
    std::vector<int> mas_right(n);

    for (int i = 0; i < n; i++) {
        int key, left, right;
        std::cin >> key >> left >> right;
        nodeArray[i] = new Node(key);
        mas_left[i] = left;
        mas_right[i] = right;
    }

    for (int i = 0; i < n; i++) {
        if (mas_left[i] != 0)
            nodeArray[i]->left = nodeArray[mas_left[i] - 1];
        if (mas_right[i] != 0)
            nodeArray[i]->right = nodeArray[mas_right[i] - 1];
    }

    postOrder(nodeArray[0]);
    Node *root = turnLeft(nodeArray[0]);
    postOrder(root);

    int place = 0;
    std::vector<Node*> nodes;
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* nowNode = q.front(); q.pop();
        nowNode->placee = ++place;
        nodes.push_back(nowNode);
        if(nowNode->left)
            q.push(nowNode->left);
        if(nowNode->right)
            q.push(nowNode->right);
    }
    std::cout << nodes.size() << "\n";
    for (size_t i = 0; i < nodes.size(); ++i) {
        Node* nowNode = nodes[i];
        int Ki = nowNode->data;
        int Li = nowNode->left ? nowNode->left->placee : 0;
        int Ri = nowNode->right ? nowNode->right->placee : 0;
        std::cout << Ki << " " << Li << " " << Ri << "\n";
    }

    return 0;
}
