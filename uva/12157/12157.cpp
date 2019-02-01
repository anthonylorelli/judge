// Problem definition: https://uva.onlinejudge.org/external/121/12157.pdf
// Accepted ?

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int count {0};
    std::cin >> count;

    std::vector<int> cases(count);
    std::iota(cases.begin(), cases.end(), 1);

    for (auto i : cases)
    {
        int callCount {0};
        std::cin >> callCount;
        std::vector<int> calls(callCount);
        std::for_each(calls.begin(), calls.end(), [&](int& n) { std::cin >> n; });
    }
}
