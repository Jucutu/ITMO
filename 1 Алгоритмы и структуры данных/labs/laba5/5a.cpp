#include <iostream>
#include <vector>

struct Node {
    int data;
    int right;
    int left;
    int countR = -1;
    int countL = -1;

    Node(int d, int l, int r) : data{ d }, left{ l }, right{ r } {}
};

class Tree {

public:
    int travset(std::vector<Node*>& arr, int ind) {
        if (arr[ind]->countR == -1) {
            if (arr[ind]->right != 0) {
                arr[ind]->countR = travset(arr, arr[ind]->right - 1);
            }
        }
        if (arr[ind]->countL == -1) {
            if (arr[ind]->left != 0) {
                arr[ind]->countL = travset(arr, arr[ind]->left - 1);
            }
        }

        return std::max(arr[ind]->countL, arr[ind]->countR) + 1;
    }
};

int main() {
    int n;
    std::cin >> n;

    Tree tr;
    std::vector<Node*> arr;
    Node* nd;
    int k, l, r;

    for (int i = 0; i < n; i++) {
        std::cin >> k >> l >> r;
        nd = new Node(k, l, r);
        arr.push_back(nd);
    }

    for (int i = 0; i < n; i++) {
        tr.travset(arr, i);
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[i]->countR - arr[i]->countL << '\n';
    }

    return 0;
}
