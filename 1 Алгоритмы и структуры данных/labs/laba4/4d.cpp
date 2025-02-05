
#include <iostream>
#include <queue>

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

    void bfs() {
        bfs(root);
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

    void  bfs(Node* root) {
        if (root == nullptr) {
            return;
        }

        std::queue<std::pair<Node*, int>> q;
        int level = -1;
        q.push({root, 0});

        while (!q.empty()) {
            std::pair<Node*, int> current = q.front();
            q.pop();

            if (current.second != level) {
                std::cout << current.first->data  << ' ';
                level++;
            }
            if (current.first->right != nullptr) {
                q.push({current.first->right, current.second + 1});
            }
            if (current.first->left != nullptr) {
                q.push({current.first->left, current.second + 1});
            }
        }
    }
};


int main() {
    int n;
    std::cin >> n;

    Tree bst;
    for (int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        bst.insert(value);
    }

    bst.bfs();

    return 0;
}

