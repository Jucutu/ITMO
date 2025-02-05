#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> marks(n);
    for (int i = 0; i < n; i++) {
        std::cin >> marks[i];
    }

    std::vector<int> prev(m, 0);
    std::vector<int> curr(m, 0);
    int max_side = 0;
    int leftCol = 0, leftRow = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (marks[i][j] == '5') {
                if (i != 0 && j != 0) {
                    curr[j] = std::min({ prev[j-1], prev[j], curr[j-1]}) + 1;
                }
                else {
                    curr[j] = 1;
                }

                if (curr[j] > max_side) {
                    max_side = curr[j];
                    leftRow = i - max_side + 1;
                    leftCol = j - max_side + 1;
                }
                else if (curr[j] == max_side) {
                    int newR = i - curr[j] + 1;
                    int newC = j - curr[j] + 1;
                    if (newR > leftRow || (leftRow == newR && newC > leftCol)) {
                        leftCol = newC, leftRow = newR;
                    }
                }
            }
            else {
                curr[j] = 0;
            }
        }
        prev = curr;
    }

    std::cout << max_side << ' ' << leftRow + 1 << ' ' << leftCol + 1 << '\n';
    return 0;
}
