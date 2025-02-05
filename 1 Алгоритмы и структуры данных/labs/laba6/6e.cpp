#include <iostream>
#include <vector>
#include <algorithm>

void heapify(std::vector<int>& numbers, int n, int i) {
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && numbers[l] > numbers[i]) {
        largest = l;
    }
    if (r < n && numbers[r] > numbers[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(numbers[i], numbers[largest]);
        heapify(numbers, n, largest);
    }
}

void heapSort(std::vector<int>& numbers, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(numbers, n, i);
    }

    for (int i = n - 1; i >= 0; --i) {
        std::swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int data;
        std::cin >> data;
        numbers.push_back(data);
    }

    heapSort(numbers, n);

    for (int i = 0; i < n; i++) {
        std::cout << numbers[i] << ' ';
    }
    return 0;
}
