#include <iostream>
//hf,jnftn working

struct Node
{
    int len;
    int height;
    Node *next;
    Node(long long len, long long height) : len(len), height(height), next(NULL) {}
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

    bool isEmpty() const
    {
        return head == NULL;
    }

    void push_back(int len, int heihgt)
    {
        Node *nd = new Node(len, heihgt);

        nd->next = head;
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

    Node *peek()
    {
        return head;
    }
};

int main() {
    int n;
    std::cin >> n;

    List ls;;
    ls.push_back(0, -1);
    long long res = 0;

    for (int i = 0; i <= n; i++)
    {
        long long h;
        if (i < n)
        {
            std::cin >> h;
        }
        else
        {
            h = 0;
        }

        long long len = i;
        while (!ls.isEmpty() && h <= ls.peek()->height)
        {
            len = ls.peek()->len;
            int hBefore = ls.peek()->height;
            ls.pop_back();

            int area = hBefore * (i - len);
            if (area > res)
            {
                res = area;
            }
        }
        ls.push_back(len, h);
    }

  std::cout << res << '\n';
  return 0;
}
