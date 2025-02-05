#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

Node* buildTreeFromPreIn(std::vector<int> preorder, std::vector<int> inorder, int preStart, int preEnd,
                         int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return nullptr;
    }

    int rootData = preorder[preStart];
    Node* root = new Node(rootData);

    int inRootIndex = 0;
    while (inRootIndex < inorder.size() && inorder[inRootIndex] != rootData) {
        inRootIndex++;
    }

    if (inRootIndex == inorder.size()) {
        return nullptr; // rootData не найден в inorder
    }

    // Левое поддерево
    root->left = buildTreeFromPreIn(preorder, inorder, preStart + 1, preStart + inRootIndex - inStart,
                                   inStart, inRootIndex - 1);

    // Правое поддерево
    root->right = buildTreeFromPreIn(preorder, inorder, preStart + inRootIndex - inStart + 1, preEnd,
                                    inRootIndex + 1, inEnd);

    return root;
}

bool checkPostorder(Node* root, std::vector<int> postorder, int& postIndex) {
    if (root == nullptr) {
        return true;
    }

    if (!checkPostorder(root->left, postorder, postIndex)) {
        return false;
    }

    if (!checkPostorder(root->right, postorder, postIndex)) {
        return false;
    }

    if (postorder[postIndex] != root->data) {
        return false;
    }

    postIndex++;
    return true;
}

std::vector<int> stringToVector(const std::string& str) {
    std::vector<int> result;
    std::string numStr;
    for (char c : str) {
        if (c == ' ') {
            if (!numStr.empty()) {
                result.push_back(std::stoi(numStr));
                numStr.clear();
            }
        } else {
            numStr += c;
        }
    }
    if (!numStr.empty()) {
        result.push_back(std::stoi(numStr));
    }
    return result;
}


int main() {
    int numVertices;
    std::cout << "Введите количество вершин: ";
    std::cin >> numVertices;

    std::cin.ignore(); // Очистка буфера ввода

    std::string preorderStr, inorderStr, postorderStr;

    std::getline(std::cin, preorderStr);

    std::getline(std::cin, inorderStr);

    std::getline(std::cin, postorderStr);

    std::vector<int> preorder = stringToVector(preorderStr);
    std::vector<int> inorder = stringToVector(inorderStr);
    std::vector<int> postorder = stringToVector(postorderStr);

    Node* root = buildTreeFromPreIn(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);

    int postIndex = 0;
    bool isValid = checkPostorder(root, postorder, postIndex);

    if (isValid) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}
