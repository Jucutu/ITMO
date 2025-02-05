#include <iostream>


struct Node
{
    int key;
    Node *next;
};

class List
{
private:
    Node *head;
    Node *tail;

public:
    List()
    {
        head = NULL;
        tail = NULL;
    }

    void push_back(int d)
    {
        Node *nd = new Node();

        nd->key = d;
        nd->next = NULL;

        if (head == NULL)
        {
            head = nd;
            tail = nd;
        }
        else
        {
            tail->next = nd;
            tail = nd;
        }
    }

    int pop_first()
    {
        Node *nd = head;

        if (head == NULL) {
            return -1;
        }

        head = head->next;
        int value = nd->key;

        delete nd;
        return value;
    }

};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;

    List ls;

    for (int i = 0; i < n; ++i)
    {
        char operation;
        std::cin >> operation;

        if (operation == '+')
        {
            int x;
            std::cin >> x;
            ls.push_back(x);
        }
        else if (operation == '-')
        {
            int deleted = ls.pop_first();
            if (deleted != -1) {
                std::cout << deleted << '\n';
            }
        }
    }
    return 0;
}

