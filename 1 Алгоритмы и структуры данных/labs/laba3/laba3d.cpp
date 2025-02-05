#include <iostream>
#include <string>
#include <algorithm>

struct Node {
    int key;
    Node* next;
};

class List {
private:
    Node* head;

public:
    List() : head(nullptr) {}

    void push_back(int d) {
        Node* nd = new Node();
        nd->key = d;
        nd->next = head;
        head = nd;
    }

    int pop_back() {
        if (head == nullptr) {
            return 0;
        }
        int value = head->key;
        Node* nd = head;
        head = head->next;
        delete nd;
        return value;
    }
};

std::string valueInt(const std::string& s, int n) {
    int i = n;
    char c = s[i];
    while (c >= '0' && c <= '9') {
        i--;
        c = s[i];
    }
    return s.substr(i + 1, n - i);
}

int main() {
    std::string s;
    std::getline(std::cin, s);

    long a[26] = {0};
    int i = s.length() - 1;
    long k = 1;

    List stack;

    while (i >= 0) {
        char c = s[i];

        if (c == '(') {
            k /= stack.pop_back();
        } else if (c >= 'A' && c <= 'Z') {
            long n = 1;
            n *= k;
            a[c - 'A'] += n;
        } else if (c >= '0' && c <= '9') {
            std::string number = valueInt(s, i);
            i -= number.length();
            long n = std::stol(number);
            char pr = s[i];

            if (pr == ')') {
                stack.push_back(n);
                k *= n;
            } else {
                a[pr - 'A'] += (n * k);
            }
        }

        i--;
    }

    // Сортировка элементов по алфавиту
    std::string result;
    for (int j = 0; j < 26; j++) {
        if (a[j] > 0) {
            result += char('A' + j);
            if (a[j] > 1) {
                result += std::to_string(a[j]);
            }
        }
    }

    std::cout << result << std::endl;

    return 0;
}
