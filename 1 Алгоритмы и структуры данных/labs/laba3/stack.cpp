#include <iostream>
//https://pro-prof.com/forums/topic/%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F-%D1%81%D0%B2%D1%8F%D0%B7%D0%BD%D1%8B%D1%85-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2-%D0%BD%D0%B0-%D1%81

struct Node
{
    int key;
    Node *next;
};

class List
{
private:
    Node *head;

public:
    List()
    {
        head = NULL;
    }

    void push_back(int d)
    {
        Node *nd = new Node();

        nd->key = d;
        nd->next = head; //nd->next = NULL;
        head = nd;
    }

    void pop_back()
    {
        Node *nd = head;

        if (head == NULL) {
            return;
        }

        head = head->next;
        delete nd;
    }

    void printList()
    {
        Node *current = head;

        while(current)
        {
            std::cout << current->key << '\n';
            current = current->next;
        }
    }
};

int main()
{
    List ls;

    ls.push_back(134);
    ls.push_back(2387);
    ls.push_back(5);
    ls.push_back(74);
    ls.push_back(0);
    ls.pop_back();

    ls.printList();

    return 0;
}

