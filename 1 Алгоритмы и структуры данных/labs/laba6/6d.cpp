#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    long long value;
};

class MinHeap {
public:
    std::vector<Node> heap;

    void push(long long val) {
        heap.push_back({val});
        siftUp(heap.size() - 1);
    }

    void pop() {
        if (!heap.empty()) {
            std::swap(heap[0], heap.back());
            heap.pop_back();
            siftDown(0);
        }
    }

    Node extractMin() {
        Node result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    long long top() const {
        return heap[0].value;
    }

private:
    void siftUp(int i) {
        while (i > 0 && heap[i].value < heap[(i - 1) / 2].value) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l].value < heap[smallest].value) {
            smallest = l;
        }
        if (r < heap.size() && heap[r].value < heap[smallest].value) {
            smallest = r;
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }
};

class MaxHeap {
public:
    std::vector<Node> heap;

    void push(long long val) {
        heap.push_back({val});
        siftUp(heap.size() - 1);
    }

    void pop() {
        if (!heap.empty()) {
            std::swap(heap[0], heap.back());
            heap.pop_back();
            siftDown(0);
        }
    }

    Node extractMax() {
        Node result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    long long top() const {
        return heap[0].value;
    }

private:
    void siftUp(int i) {
        while (i > 0 && heap[i].value > heap[(i - 1) / 2].value) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l].value > heap[largest].value) {
            largest = l;
        }
        if (r < heap.size() && heap[r].value > heap[largest].value) {
            largest = r;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            siftDown(largest);
        }
    }
};

int main() {
    int n;
    std::cin >> n;

    MinHeap minHeap;
    MaxHeap maxHeap;

    for (int i = 0; i < n; ++i) {
        long long bright;
        std::cin >> bright;

        if (maxHeap.empty() || bright <= maxHeap.top()) {
            maxHeap.push(bright);
        }
        else {
            minHeap.push(bright);
        }

        if (minHeap.heap.size() > maxHeap.heap.size()) {
            maxHeap.push(minHeap.extractMin().value);
        }
        if (maxHeap.heap.size() > minHeap.heap.size() + 1) {
            minHeap.push(maxHeap.extractMax().value);
        }

        long long median;
        if (maxHeap.heap.size() == minHeap.heap.size()) {
            median = (maxHeap.top() + minHeap.top()) / 2;
        }
        else {
            median = maxHeap.top();
        }

        std::cout << median << '\n';
    }
    return 0;
}
