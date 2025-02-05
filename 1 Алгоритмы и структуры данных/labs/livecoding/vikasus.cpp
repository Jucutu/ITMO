#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string number;
    int digitSum;
    int modulo;
};

int main() {
    int N;
    cin >> N;
    if (N == 0) {
        cout << 0 << endl;
        return 0;
    }

    queue<Node> q;
    vector<bool> seen(10000, false);

    for (int d = 1; d <= 9; ++d) {
        if (d == N && d % N == 0) {
            cout << d << endl;
            return 0;
        }
        if (d <= N + 9) {
            q.push({to_string(d), d, d % N});
            seen[newSum * N + newMod] = true;
        }
    }

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        for (int d = 0; d <= 9; ++d) {
            int newSum = current.digitSum + d;
            if (newSum > N + 9) continue;

            int newMod = (current.modulo * 10 + d) % N;

            if (newSum == N && newMod == 0) {
                cout << current.number + to_string(d) << endl;
                return 0;
            }

            if (!seen[newSum * N + newMod]) {
                seen[newSum * N + newMod] = true;
                q.push({current.number + to_string(d), newSum, newMod});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
