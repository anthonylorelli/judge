// Problem definition: https://uva.onlinejudge.org/external/119/11942.pdf
// Accepted 2019-01-30

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int lines {0};
    std::cin >> lines;
    constexpr int lineLength {10};

    std::cout << "Lumberjacks:\n";

    while (lines--)
    {
        std::vector<int> beards;
        for (int i = 0; i < lineLength; ++i)
        {
            int measurement {0};
            std::cin >> measurement;
            beards.push_back(measurement);
        }

        if (std::is_sorted(std::begin(beards), std::end(beards)) ||
            std::is_sorted(std::begin(beards), std::end(beards), 
                [](int m, int n) { return m > n; }))
        {
            std::cout << "Ordered\n";
        }
        else
        {
            std::cout << "Unordered\n";
        }
    }
}
