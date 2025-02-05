#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    long long time;
    long long salary;
};

class SalaryHeap {
public:
    std::vector<Node> heap;

    void push(const Node& val) {
        heap.push_back(val);
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
        if (heap.empty()) {
            return Node{ -1, -1 };
        }
        Node result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    void heapify(int i) {
        siftDown(i);
    }

    void siftUp(int i) {
        while (i > 0 && heap[i].salary < heap[(i - 1) / 2].salary) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l].salary < heap[smallest].salary) {
            smallest = l;
        }
        if (r < heap.size() && heap[r].salary < heap[smallest].salary) {
            smallest = r;
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }
};

class TimeHeap {
public:
    std::vector<Node> heap;

    void push(const Node& val) {
        heap.push_back(val);
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
        if (heap.empty()) {
            return Node{ -1, -1 };
        }
        Node result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    void heapify(int i) {
        siftDown(i);
    }

    void siftUp(int i) {
        while (i > 0 && heap[i].time < heap[(i - 1) / 2].time) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l].time < heap[smallest].time) {
            smallest = l;
        }
        if (r < heap.size() && heap[r].time < heap[smallest].time) {
            smallest = r;
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }
};


int main() {
    SalaryHeap free;
    TimeHeap busy;
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        Node x;
        std::cin >> x.salary;
        x.time = 0;
        free.push(x);
    }

    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        long long t, f;
        std::cin >> t >> f;

        while (!busy.empty() && busy.heap[0].time <= t) {
            free.push(busy.heap[0]);
            busy.extractMin();
        }

        if (!free.empty()) {
            Node maker = free.extractMin();
            ans += maker.salary * f;
            maker.time = t + f;
            busy.push(maker);
        }
    }

    std::cout << ans;
    return 0;
}
