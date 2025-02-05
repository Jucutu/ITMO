#include <iostream>
#include <vector>

class PriorityQueue {
public:
    std::vector<std::vector<long long >> queues;

    void sift_up(std::vector<long long>& heap, long long i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapify(std::vector<long long>& arr, long long i) {
        int largest = i;

        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < arr.size() && arr[l] < arr[largest]) {
            largest = l;
        }
        if (r < arr.size() && arr[r] < arr[largest]) {
            largest = r;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, largest);
        }
    }

    void create() {
        queues.emplace_back();
    }

    void insert(long long k, long long x) {
        queues[k].push_back(x);
        sift_up(queues[k], queues[k].size() - 1);
    }

    void extract_min(long long k) {
        if (!queues[k].empty()) {
            long long min = queues[k][0];
            std::swap(queues[k][0], queues[k].back());
            queues[k].pop_back();
            heapify(queues[k], 0);
            std::cout << min << '\n';
        }
        else {
            std::cout << '*' << '\n';
        }
    }

    void decrease_key(long long k, long long x, long long y) {
        for (int i = 0; i <= queues[k].size() - 1; i++) {
            if (queues[k][i] == x) {
                queues[k][i] = y;
                break;
            }
        }
        for (int i = queues[k].size() / 2; i >= 0; i--) {
            heapify(queues[k], i);
        }
    }

    void merge(long long k, long long m) {
        create();
        long long s = queues.size() - 1;
        if (!queues[k].empty()) {
            for (int i = 0; i < queues[k].size(); ++i) {
                queues[s].push_back(queues[k][i]);
            }
        }
        if (!queues[m].empty()) {
            for (int i = 0; i < queues[m].size(); ++i) {
                queues[s].push_back(queues[m][i]);
            }
        }
        if (!queues[s].empty()) {
            for (int i = (queues[s].size() - 1) / 2; i >= 0; --i) {
                heapify(queues[s], i);
            }
        }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    PriorityQueue a;
    long long k, m, x, y;
    std::string command;
    while (std::cin >> command) {
        if (command == "create") {
            a.create();
        }
        else if (command == "insert") {
            std::cin >> k >> x;
            a.insert(k, x);
        }
        else if (command == "extract-min") {
            std::cin >> k;
            a.extract_min(k);
        }
        else if (command == "merge") {
            std::cin >> k >> m;
            a.merge(k, m);
        }
        else if (command == "decrease-key") {
            std::cin >> k >> x >> y;
            a.decrease_key(k, x, y);
        }
    }
    return 0;
}
