#include <iostream>
#include <vector>
#include <algorithm>


bool countFractions(std::vector<int>& numbers, double mid, int k, int n)
{
    int count = 0;
    std::vector<std::pair<int, int>> fractions;
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (double(double(numbers[i]) / double(numbers[i])) <= mid)
            {
                count++;
                if (count == k)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int binSearch(int n, int k, std::vector<int>& numbers)
{
    double l = 0;
    double r = 1e9;

    while (r - l > 1e-9)
    {
        double m = (l + r) / 2;
        if (countFractions(numbers, m, k, n))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }

    for (int i = 0; i < numbers.size(); ++i)
    {
        for (int j = i + 1; j < numbers.size(); ++j)
        {
            if (double(double(numbers[i]) / double(numbers[j])) <= l)
            {
                k--;
                if (k == 0) {
                    std::cout << numbers[i] << " " << numbers[j];
                    return 0;
                }
            }
        }
    }
    return 0;
}


int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> numbers(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> numbers[i];
    }

    binSearch(n, k, numbers);

}
