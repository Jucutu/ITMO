#include <iostream>
#include <vector>

bool isMinHeap(const std::vector<int>& numbers, int n) {
    bool result = true;
    for (int i = 1; i < n; i++) {
        if (2 * i - 1 < n && numbers[i - 1] > numbers[2 * i - 1]) {
            return false;
        }
        if (2 * i < n && numbers[i - 1] > numbers[2 * i]) {
            return false;
        }
    }
    return result;
}


int main() {
    int n;
    std::cin >> n;

    std::vector<int> numbers;
    for (int i = 0; i < n; ++i) {
        int data;
        std::cin >> data;
        numbers.push_back(data);
    }

    if (isMinHeap(numbers, n))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    return 0;
}
