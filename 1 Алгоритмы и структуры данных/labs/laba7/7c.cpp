#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long n, m;
    std::cin >> n >> m;

    std::vector<std::vector<long long>> sum(n);

    for (int i = 0; i < n; i++) {
        int sitting;
        std::cin >> sitting;

        std::vector<long long> som(sitting);

        for (int j = 0; j < sitting; j++) {
            std::cin >> som[j];
        }

        std::vector<long long> prefix_right(sitting + 1, 0);

        for (int x = 1; x < sitting + 1; x++) {
            prefix_right[x] = prefix_right[x - 1] + som[sitting - x];
        }

        std::vector<long long> prefix_left(sitting + 1, 0);

        for (int y = 1; y < sitting + 1; y++) {
            prefix_left[y] = prefix_left[y - 1] + som[y - 1];
        }

        std::vector<long long> current_sum(sitting + 1, 0);

        for (int z = 0; z <= sitting; z++) {
            for (int k = 0; k < z + 1; k++) {
                int t = z - k;
                if (t + k <= sitting) {
                    current_sum[z] = std::max(current_sum[z], prefix_left[k] + prefix_right[t]);
                }
            }
        }

        sum[i] = current_sum;
    }

    std::vector<long long> dp(m + 1, 0);

    for (int i = 0; i < n; i++) {
        const std::vector<long long>& row = sum[i];
        
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= row.size() - 1; k++) {
                if (j >= k) {
                    dp[j] = std::max(dp[j], dp[j - k] + row[k]);
                }
            }
        }
    }

    std::cout << dp[m];
    return 0;
}
