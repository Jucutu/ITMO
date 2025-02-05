#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long int end_time = 0;
    long long int salary;
};

struct Heap {
    vector<Node> h;

    void delete_time(vector<Node> &arr) {
        swap(arr[0], arr[arr.size() - 1]);
        arr.pop_back();
        heapify_time(arr, 0);
    }

    void delete_salary(vector<Node> &arr) {
        swap(arr[0], arr[arr.size() - 1]);
        arr.pop_back();
        heapify_salary(arr, 0);
    }

    void sift_up_time(vector<Node> &arr, long long i) {
        long long parent = (i - 1) / 2;
        if (parent >= 0 and arr[i].end_time < arr[parent].end_time) {
            swap(arr[i], arr[parent]);
            sift_up_time(arr, parent);
        }
    }

    void sift_up_salary(vector<Node> &arr, long long i) {
        long long parent = (i - 1) / 2;
        if (parent >= 0 and arr[i].salary < arr[parent].salary) {
            swap(arr[i], arr[parent]);
            sift_up_salary(arr, parent);
        }
    }

    void heapify_time(vector<Node> &arr, long long i) {
        long long size = arr.size();

        long long int largest = i;
        long long int l = 2 * i + 1;
        long long int r = 2 * i + 2;

        if (l < size && arr[l].end_time < arr[largest].end_time) {
            largest = l;
        }


        if (r < size && arr[r].end_time < arr[largest].end_time) {
            largest = r;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify_time(arr, largest);
        }
    }

    void heapify_salary(vector<Node> &arr, long long i) {
        long long size = arr.size();

        long long int largest = i;
        long long int l = 2 * i + 1;
        long long int r = 2 * i + 2;

        if (l < size && arr[l].salary < arr[largest].salary) {
            largest = l;
        }


        if (r < size && arr[r].salary < arr[largest].salary) {
            largest = r;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify_salary(arr, largest);
        }
    }


    void add_time(long long int t, long long int f, long long int &ans) {
        h[0].end_time = t + f;
        ans += f * h[0].salary;
    }
};

int main() {

    Heap busy, free;
    long long int n, m, ans = 0;
    cin >> n >> m;

    for (long long int i = 0; i < n; ++i) {
        Node x;
        cin >> x.salary;
        free.h.push_back(x);
    }
    for (int i = n / 2; i >= 0; --i) {
        free.heapify_salary(free.h, i);
    }

    for (long long int i = 0; i < m; ++i) {
        long long int t, f;
        cin >> t >> f;
        while (!busy.h.empty() and busy.h[0].end_time <= t) {
            free.h.push_back(busy.h[0]);
            free.sift_up_salary(free.h, free.h.size() - 1);
            busy.delete_time(busy.h);

        }

        if (!free.h.empty()) {
            free.add_time(t, f, ans);
            busy.h.push_back(free.h[0]);
            busy.sift_up_time(busy.h, busy.h.size() - 1);
            free.delete_salary(free.h);
        }
    }

    cout << ans;

    return 0;
}
