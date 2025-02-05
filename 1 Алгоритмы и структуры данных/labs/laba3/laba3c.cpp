#include <iostream>
#include <vector>

void merge(std::vector<std::string>& arr, long long left, long long mid, long long right, long long k)
{
    long long it1 = 0;
    long long it2 = 0;
    std::vector<std::string> res(right - left);
    while ((left + it1 < mid) && (mid + it2 < right))
    {
        if (arr[left + it1][k] < arr[mid + it2][k])
        {
             res[it1 + it2] = arr[left + it1];
             it1++;
        }
        else
        {
             res[it1 + it2] = arr[mid + it2];
             it2++;
        }
    }
    while ((left + it1) < mid)
    {
        res[it1 + it2] = arr[left + it1];
        it1++;
    }
    while ((mid + it2) < right)
    {
        res[it1 + it2] = arr[mid + it2];
        it2++;
    }
    for (int i = 0; i < (it1 + it2); i++)
    {
        arr[left + i] = res[i];
    }
}


void mergesort(std::vector<std::string>& a, long long l, long long r, long long k)
{
    if (l + 1 < r)
    {
        long long m = (l + r) / 2;
        mergesort(a, l, m, k);
        mergesort(a, m, r, k);
        merge(a, l, m, r, k);
    }
}


int main(void)
{
    long long n, k, t;
    std::cin >> n >> k >> t;
    std::vector<std::string> words(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> words[i];
    }
    for (int i = 0; i < t; i++)
    {
        mergesort(words, 0, n, i + 1);
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << words[i] << '\n';
    }
    return 0;
}
